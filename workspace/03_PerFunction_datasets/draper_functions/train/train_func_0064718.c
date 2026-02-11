ditherRGBvals(int x, int y, int r, int g, int b)
{
  int xdith, ydith;

  xdith = x % 16;
  ydith = y % 16;
  return mgx11colors[DMAP(r, xdith, ydith) +
              mgx11multab[DMAP(g, xdith, ydith) +
	      mgx11multab[DMAP(b, xdith, ydith)]]];
}
