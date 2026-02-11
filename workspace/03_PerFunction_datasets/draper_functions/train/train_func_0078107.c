gridupdate (struct state *st, Bool interruptible)
{
  int x, y;
  if (st->gridden > 0)
    for (x = 0; x <= xmax && !(wasakeypressed (st) && interruptible); x += st->boxw)
      for (y = 0; y <= ymax; y += st->boxh)
	{
	  if (random1 (15) < st->gridden)
	    {
#define lesser(A,B) ( ((A)<(B)) ? (A) : (B) )
	      int max = lesser (x + st->boxw, xmax);
	      int xc;
	      for (xc = x; xc <= max; xc++)
		sp (st, xc, y, 1);
	    }
	  if (random1 (15) < st->gridden)
	    {
	      int max = lesser (y + st->boxh, ymax);
	      int yc;
	      for (yc = y; yc <= max; yc++)
		sp (st, x, yc, 1);
	    }
	}
}
