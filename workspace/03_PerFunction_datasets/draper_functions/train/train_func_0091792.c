x_destroy (XDR *xdrs)
{
  xdrs->x_handy = 0;
  xdrs->x_base = 0;
  if (xdrs->x_private)
    {
      free (xdrs->x_private);
      xdrs->x_private = NULL;
    }
  return;
}
