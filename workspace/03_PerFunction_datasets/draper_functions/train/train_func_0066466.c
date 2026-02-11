GetMouseData (uint32 (&d)[3])
{
  int x, y;
  uint32 t;


  if (FCEUMOV_Mode (MOVIEMODE_PLAY))
    return;


  t = SDL_GetMouseState (&x, &y);
  SDL_Event event;
#ifdef _GTK
  if (noGui == 0)
    {


      int fullscreen = 0;
      g_config->getOption ("SDL.Fullscreen", &fullscreen);
      if (fullscreen == 0)
	{
	  x = GtkMouseData[0];
	  y = GtkMouseData[1];
	  t = GtkMouseData[2];
	}
    }
#endif

  d[2] = 0;
  if (t & SDL_BUTTON (1))
    {
      d[2] |= 0x1;
    }
  if (t & SDL_BUTTON (3))
    {
      d[2] |= 0x2;
    }


  t = PtoV (x, y);
  d[0] = t & 0xFFFF;
  d[1] = (t >> 16) & 0xFFFF;


}
