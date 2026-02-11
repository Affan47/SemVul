precoord(node *nuroot,boolean *subtree,double *tipmax,long *across)
{


  double oldtipmax, minimum;
  long i, maxchar;

  (*tipmax) = 0.0;
  if ((*subtree))
    maxchar = vscreenwidth - 13;
  else
    maxchar = vscreenwidth - 5;
  (*across) = maxchar;
  ltrav_(nuroot, 0.0, 0.0, tipmax, across, &maxchar);
  i = 0;
  do {
    oldtipmax = (*tipmax);
    minimum = 3.0 / (*across) * (*tipmax);
    ltrav_(nuroot, 0.0, minimum, tipmax, across, &maxchar);
    i++;
  } while (fabs((*tipmax) - oldtipmax) > 0.01 * oldtipmax && i <= 40);
}
