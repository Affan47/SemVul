xdrstdio_getlong (XDR *xdrs, long *lp)
{
  u_int32_t mycopy;

  if (fread ((caddr_t) &mycopy, 4, 1, (FILE *) xdrs->x_private) != 1)
    return FALSE;
  *lp = (long) ntohl (mycopy);
  return TRUE;
}
