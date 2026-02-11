ds_setn(Ds *dsx, unsigned char *s, size_t slen)
{
  Ds *ds;

  if (dsx == NULL) {
	if ((ds = ds_init(NULL)) == NULL)
	  return(NULL);
  }
  else {
	ds = dsx;
	ds_reset(ds);
  }

  if (ds_copyb(ds, s, slen, 0) == NULL)
	return(NULL);

  return(ds);
}
