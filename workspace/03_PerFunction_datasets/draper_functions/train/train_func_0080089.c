get_distance_and_dir_smooth(int h, int h1, int *dir)
{
  unsigned int x_diff = abs(spr[h].x - spr[h1].x);
  unsigned int y_diff = abs(spr[h].y - spr[h1].y);

  if (spr[h].x < spr[h1].x)
    {
      if (spr[h].y < spr[h1].y)
	{

	  if (y_diff * 4 < x_diff)
	    *dir = 6;
	  else if (x_diff * 4 < y_diff)
	    *dir = 2;
	  else
	    *dir = 3;
	}
      else if (spr[h].y > spr[h1].y)
	{

	  if (y_diff * 4 < x_diff)
	    *dir = 6;
	  else if (x_diff * 4 < y_diff)
	    *dir = 8;
	  else
	    *dir = 9;
	}
      else
	{
	  *dir = 6;
	}
    }
  else if (spr[h].x > spr[h1].x)
    {
      if (spr[h].y < spr[h1].y)
	{

	  if (y_diff * 4 < x_diff)
	    *dir = 4;
	  else if (x_diff * 4 < y_diff)
	    *dir = 2;
	  else
	    *dir = 1;
	}
      else if (spr[h].y > spr[h1].y)
	{

	  if (y_diff * 4 < x_diff)
	    *dir = 4;
	  else if (x_diff * 4 < y_diff)
	    *dir = 8;
	  else
	    *dir = 7;
	}
      else
	{
	  *dir = 4;
	}
    }
  else
    {
      if (spr[h].y < spr[h1].y)
	*dir = 2;
      else if (spr[h].y > spr[h1].y)
	*dir = 8;
    }

  return (x_diff > y_diff) ? x_diff : y_diff;
}
