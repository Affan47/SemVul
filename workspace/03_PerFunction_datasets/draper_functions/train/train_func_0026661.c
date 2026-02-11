process_animated_tiles(void)
{
  int flip;


  if (water_timer < thisTickCount)
    {

      water_timer = thisTickCount + (rand() % 2000);
      flip = rand() % 2;

      int x = 0;
      for (; x < 96; x++)
	{
	  int screen_square_full_idx0 = pam.t[x].square_full_idx0;
	  int start_full_idx0 = (8-1) * 128;
	  if (screen_square_full_idx0 >= start_full_idx0
	      && screen_square_full_idx0 < (start_full_idx0 + 128))
	    gfx_tiles_draw((8-1) + flip, screen_square_full_idx0 % 128, x);
	}
    }


  {
    fire_flip--;
    if (fire_flip < 0)
      fire_flip = 4;

    int x = 0;
    for (; x < 96; x++)
      {
	int screen_square_full_idx0 = pam.t[x].square_full_idx0;
	int start_full_idx0 = (19-1) * 128;
	if (screen_square_full_idx0 >= start_full_idx0
	    && screen_square_full_idx0 < (start_full_idx0 + 128))
	  gfx_tiles_draw((19-1) + fire_flip, screen_square_full_idx0 % 128, x);
      }
  }
}
