xdrrec_getint32 (XDR *xdrs, int32_t *ip)
{
  RECSTREAM *rstrm = (RECSTREAM *) xdrs->x_private;
  int32_t *bufip = (int32_t *) rstrm->in_finger;
  int32_t mylong;


  if (rstrm->fbtbc >= BYTES_PER_XDR_UNIT &&
      rstrm->in_boundry - (char *) bufip >= BYTES_PER_XDR_UNIT)
    {
      *ip = ntohl (*bufip);
      rstrm->fbtbc -= BYTES_PER_XDR_UNIT;
      rstrm->in_finger += BYTES_PER_XDR_UNIT;
    }
  else
    {
      if (!xdrrec_getbytes (xdrs, (caddr_t) &mylong,
			    BYTES_PER_XDR_UNIT))
	return FALSE;
      *ip = ntohl (mylong);
    }
  return TRUE;
}
