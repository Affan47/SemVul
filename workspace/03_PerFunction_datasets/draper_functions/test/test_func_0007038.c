process_events(void)
{
  SDL_Event event;
  int ret = 1;
  while ( SDL_PollEvent(&event) >= 1 )
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  ret = 0;
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      paused = 1 - paused;
	      break;
	    case SDLK_s:
	      SDL_SaveBMP(sprite_global.display,"screenshot.bmp");
	      break;
	    default:
	      break;
	    }
	  break;
	default:
	  break;
	}
    }
  return ret;
}
