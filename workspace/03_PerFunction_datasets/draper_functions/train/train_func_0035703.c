pix_x (GSCHEM_TOPLEVEL *w_current, int val)
{

  double i;
  int j;

  i = w_current->toplevel->page_current->to_screen_x_constant *
        (double)(val - w_current->toplevel->page_current->left);

#ifdef HAS_RINT
  j = rint(i);
#else
  j = i;
#endif


  if (j >= 32768) {
    j = 32767;
  }
  if (j <= -32768) {
    j = -32767;
  }

  return(j);
}
