backpage(int f, int n)
{

    if (f == FALSE) {
	n = curwp->w_ntrows - 2;
	if (n <= 0)
	  n = 1;
    } else if (n < 0)
      return (forwpage(f, -n));
#if     CVMVAS
    else
      n *= curwp->w_ntrows;
#endif
    return (scrollback (n, TRUE));
}
