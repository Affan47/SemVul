points ()
{
  register unsigned int x, y, c;
  Point          *p, *lp;
#ifdef MITSHM
  if (shm)
    {
      shmpoints ();
      return;
    }
#endif
  for (x = 0; x < 256 >> CCONST; x++)
    nmypixels[x] = 0;
  lp = &point[MAXPOINT];
  for (p = point; p < lp; p++)
    {
      if (p->time > 0)
	{
	  p->time--;
	  x = (p->x += p->xp) >> 8;
	  y = (p->y += p->yp) >> 8;
	  if (x > 0 && x < MAPWIDTH &&
	      y > 0 && y < MAPHEIGHT)
	    {
	      c = p->color >> CCONST;
	      mypixels[c][nmypixels[c]].x = x;
	      mypixels[c][nmypixels[c]].y = y;
	      nmypixels[c]++;
	    }
	  else
	    p->time = 0;
	}
    }
  for (x = 0; x < 256 >> CCONST; x++)
    {
      if (nmypixels[x])
	{
	  SetColor ((x << CCONST) + PCONST);
	  XDrawPoints (dp, current.pixmap, gc, mypixels[x], nmypixels[x], CoordModeOrigin);
	}
    }
}
