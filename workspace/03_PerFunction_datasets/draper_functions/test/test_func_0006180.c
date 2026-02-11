init()
{
  if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) ) {
    cerr << "Cannot initialize SDL, exiting." << endl;
    exit(1);
  }
  SDL_ShowCursor(SDL_DISABLE);
  atexit(SDL_Quit);
#ifndef NONET
  if(SDLNet_Init()==-1) {
    cerr << "SDLNet_Init: " << SDLNet_GetError() << endl;
    exit(2);
  }
#endif

#ifdef AUDIO
  atexit(SDL_CloseAudio);

  desired.freq=44100;
  desired.format = AUDIO_S16;
  desired.samples=512;
  desired.channels=1;
  desired.callback=AudioCallBack;
  desired.userdata=NULL;

  if(SDL_OpenAudio(&desired,&obtained)<0){
    printf("Cannot open the audio device\n");
  }

  ClearPlayingSounds();

  SDL_PauseAudio(0);
#endif

  SDL_WM_SetCaption("GPL Arcade Volleyball", "GAV");

  setThemeDir(TH_DIR);
  videoinfo = SDL_GetVideoInfo();
  controlsArray = new ControlsArray();
  if ( configuration.loadConfiguration() == -1 ) {
    cerr << "Configuration file " << configuration.confFileName() <<
      " not found: creating.\n";
    if ( configuration.createConfigurationFile() == -1 )
      perror("creation failed: ");
  }

  applyConfiguration();
}
