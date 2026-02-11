redraw_arrows()
{
  int i;
  for (i=0; i<8; i++)
  {
    if (arrowsy[i])
      put_picture(arrow, arrowsx[i]-arrow->w/2, arrowsy[i],
		  0, 0, arrow->w, arrow->h);
  }
}
