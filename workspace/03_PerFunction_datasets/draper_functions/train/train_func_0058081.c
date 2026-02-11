GetDisplay()
  {
      static Display d;


      if(!d.me)	d.me = SDL_GetVideoSurface();
      return d;
  }
