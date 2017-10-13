#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defs.h"
#include "Globals.h"
#include "Funcoes.h"

int main(int argc, char *argv[]){
	int i, j;            // control
	IMAG limite, score;
	SDL_Rect scoreRect;
	SDL_Rect vidaRect;
	SDL_Rect nomeRect;

	switch(argc){
		case 2 : sscanf(argv[1],"%s",nome);
		//Defaults' mode 640x480
		case 1 : {  if(init("640","480")==1){
						return 1;
		            }
		        	break;
		         }
		case 4 : {  if(!isalpha(argv[1]) || !isalpha())
			        if(init(argv[1],argv[2]) == 1){
						 return 1;
		            }
					sscanf(argv[3],"%s",nome);
                    break;
				 }
		default:
		    puts("Inicializar com Largura Altura Nome OU Nome apenas");
		    return 1;	 
	}
	
    //void createNPC(NPC *p,int x,int y,int w,int h,int velX,int velY,char path[]){
	if(loadSound() != 0){
		return 1;
	}
	menu();
	loadMedia(&limite.texture,"borda.png");
	limite.rect.x = (WIDTH / 4) - 10;
	limite.rect.y = 0;
	limite.rect.w = (WIDTH / 4) * 3 + 10;
	limite.rect.h = HEIGHT;
	loadMedia(&score.texture,"score.png");
	score.rect.x = 0;
	score.rect.y = 0;
	score.rect.w = 157;
	score.rect.h = HEIGHT;

	//createFontTexture(&scoreTexture,gFont, 255, 0, 0);
	//SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
	//scoreRect.x = 0;
	scoreRect.y = 0;
	createNPC(&ball,WIDTH/2,HEIGHT/2,20,19,0,5,"ball.png");
   	createBricks(lvl);

	createNPC(&plataform,WIDTH/2,0.9*HEIGHT,200,25,23,23,"plataform.png");
	while(play){
		if(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					play = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							menu();
							break;
						case SDLK_LEFT:
							if(plataform.rect.x < WIDTH / 4  + WIDTH / 48){
								plataform.rect.x -= 0;
							}else{
								plataform.rect.x -= plataform.velX;
							}
							break;
						case SDLK_RIGHT:
							if(plataform.rect.x > WIDTH - plataform.rect.w - WIDTH / 32){
								plataform.rect.x += 0;
							}else{
								plataform.rect.x += plataform.velX;
							}
							break;
					}
					break;
			}
		}

		if (vida <= 0) gameOver();

		moveNPC(&ball);
		if (pointsForLife >= 10000)
		{
			vida = vida +1;
			pointsForLife -= 10000;
		}
		sprintf(scoreStr, "%d", points);
		sprintf(vidaStr, "%d", vida);
        createFontTexture(&scoreTexture,gFont, 255, 0, 0, scoreStr);
        createFontTexture(&vidaTexture,gFont, 0, 255, 0, vidaStr);
        createFontTexture(&nomeTexture,gFont,0,255,0,nome);
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
        SDL_QueryTexture(vidaTexture, NULL, NULL, &vidaRect.w, &vidaRect.h);
        SDL_QueryTexture(nomeTexture,NULL,NULL,&nomeRect.w,&nomeRect.h);
		scoreRect.x = WIDTH / 12;
		scoreRect.y = HEIGHT / 8;
		vidaRect.x = WIDTH / 10;
		vidaRect.y = (HEIGHT / 8) * 7;
		nomeRect.x = WIDTH/18;
		nomeRect.y = HEIGHT/5;

		SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
		SDL_RenderClear(gRenderer);
		//SDL_RenderCopy(borda);
		//colocar score
		SDL_RenderCopy(gRenderer,score.texture,NULL,&score.rect);
		SDL_RenderCopy(gRenderer,limite.texture,NULL,&limite.rect);
		SDL_RenderCopy(gRenderer,ball.texture,NULL,&ball.rect);
		SDL_RenderCopy(gRenderer,plataform.texture,NULL,&plataform.rect);
        for (i = 0; i < ROWS ; i++)
            for (j =0; j < COLS;j++){
                SDL_RenderCopy(gRenderer,brick[i][j].texture,NULL,&brick[i][j].rect);
	        }
        SDL_RenderCopy(gRenderer, scoreTexture, NULL, &scoreRect);
        SDL_RenderCopy(gRenderer, vidaTexture, NULL, &vidaRect);
        SDL_RenderCopy(gRenderer,nomeTexture,NULL,&nomeRect);
        SDL_RenderPresent(gRenderer);
		SDL_Delay(16);

	}

	TTF_CloseFont(gFont);
	TTF_Quit();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_DestroyTexture(ball.texture);
	SDL_DestroyTexture(plataform.texture);
	for (i = 0; i < ROWS ; i++)
            for (j =0; j < COLS;j++){
                SDL_DestroyTexture(brick[i][j].texture);
            }
	SDL_Quit();

	return 0;
}
