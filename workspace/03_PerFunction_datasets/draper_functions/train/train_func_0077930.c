ds_subst(Ds *ds, unsigned char ch_src, unsigned char ch_rpl)
{
  int i;
  unsigned char *p;

  p = (unsigned char *) ds_buf(ds);
  for (i = 0; i < ds_len(ds); i++) {
	if (*p == ch_src)
	  *p = ch_rpl;
	p++;
  }

  return(ds);
}
