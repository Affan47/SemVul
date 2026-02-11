draw_hard_tile(int x1, int y1, int tile)
{
  SDL_Rect dst;
  dst.w = 1;
  dst.h = 1;

  int x = 0;
  for (x = 0; x < 50; x++)
    {
      int y = 0;
      for (y = 0; y < 50; y++)
	{
	  if (hmap.htile[tile].x[x].y[y] == 1)
	    {

	      dst.x = x1 + x
		+ 20;
	      dst.y = y1 + y;

	      SDL_FillRect(GFX_lpDDSBack, &dst,
			   SDL_MapRGB(GFX_lpDDSBack->format, 255, 255, 255));
	    }
	}
    }
}
