xdrstdio_getbytes (XDR *xdrs, const caddr_t addr, u_int len)
{
  if ((len != 0) && (fread (addr, (int) len, 1,
			    (FILE *) xdrs->x_private) != 1))
    return FALSE;
  return TRUE;
}
