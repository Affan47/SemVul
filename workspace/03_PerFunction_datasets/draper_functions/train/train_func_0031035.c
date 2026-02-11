offset_overlap_p (HOST_WIDE_INT c, int xsize, int ysize)
{
  return (xsize == 0 || ysize == 0
	  || (c >= 0
	      ? (abs (xsize) > c)
	      : (abs (ysize) > -c)));
}
