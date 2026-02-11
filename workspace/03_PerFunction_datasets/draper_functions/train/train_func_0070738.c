handleEvents( GameStates &gameState ) {
  SDL_Event event;

  while ( SDL_PollEvent(&event) ) {
    switch(event.type) {
      case SDL_KEYDOWN: {
        switch ( event.key.keysym.sym ) {
          case SDLK_1: {
            playerOneLightFighter = !playerOneLightFighter;
            break;
          }
          case SDLK_2: {
            playerTwoLightFighter = !playerTwoLightFighter;
            break;
          }
          case SDLK_F5: {
            SDL_WM_ToggleFullScreen( screen );
            break;
          }
          case SDLK_F7: {
            if ( playMusicOn ) {
              playMusicOn = false;
              mixer.stopMusic();
            } else {
              playMusicOn = true;
              mixer.playMusic( MUSIC_INTRO, -1, 1000 );
            }
            break;
          }
          case SDLK_UP: {
            mixer.playSample( choose, 0 );
            activeChoice--;
            if ( activeChoice < 0 ) activeChoice = NR_DIFFICULTY_CHOICES - 1;
            break;
          }
          case SDLK_DOWN: {
            mixer.playSample( choose, 0 );
            activeChoice = (activeChoice + 1) % NR_DIFFICULTY_CHOICES;
            break;
          }
          case SDLK_ESCAPE: {
            gameState = GS_INTRO;
            break;
          }
          case SDLK_RETURN: {
            mixer.playSample( confirm, 0 );
            switch (activeChoice) {
              case DIFFICULTY_0: {
                difficultyLevel = 0;
	              gameState = GS_PLAYON;
                break;
              }
              case DIFFICULTY_1: {
                difficultyLevel = 1;
                gameState = GS_PLAYON;
                break;
	            }
              case DIFFICULTY_2: {
                difficultyLevel = 2;
                gameState = GS_PLAYON;
                break;
              }
              case DIFFICULTY_3: {
                difficultyLevel = 3;
                gameState = GS_PLAYON;
                break;
              }
              case BACK_TO_MAIN_MENU: {
                gameState = GS_INTRO;
                break;
              }
   	        }
            break;
  	      }
          default: break;
  	    }
        break;
      }
      case SDL_QUIT: {
        gameState = GS_QUIT;
         break;
      }
      default: break;
    }
  }
}
