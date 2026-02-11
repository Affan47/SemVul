autoclick(int x, int y)
{
  int dx, dy, nflags=0, nfills=0, rv=0;
  for (dx=-1; dx<=1; dx++)
    for (dy=-1; dy<=1; dy++)
    {
      int g = GRID(x+dx,y+dy);
      if (g == C_FLAG)
	nflags++;
      if (g == C_FILL || g == C_HUH)
	nfills++;
    }
  if (nflags == neighbors[x][y])
  {
    for (dx=-1; dx<=1; dx++)
      for (dy=-1; dy<=1; dy++)
      {
	int g = GRID(x+dx,y+dy);
	if (g == C_FILL || g == C_HUH)
	{
	  rv=1;
	  if (bomb[x+dx][y+dy])
	    do_bomb(x+dx, y+dy);
	  else if (neighbors[x+dx][y+dy] == 0)
	    flood_fill(x+dx, y+dy);
	  else
	    set_grid(x+dx, y+dy, neighbors[x+dx][y+dy]);
	}
      }
  }
  else if (nfills+nflags == neighbors[x][y])
  {
    for (dx=-1; dx<=1; dx++)
      for (dy=-1; dy<=1; dy++)
      {
	int g = GRID(x+dx,y+dy);
	if (g == C_FILL || g == C_HUH)
	{
	  rv=1;
	  set_grid(x+dx, y+dy, C_FLAG);
	  untagged--;
	  show_untagged();
	}
      }
  }
  return rv;
}
