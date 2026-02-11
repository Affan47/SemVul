ds_chop(Ds *ds, size_t chop)
{
  size_t new_len;

  if (chop > ds->len)
	return(ds->len);

  ds->len -= chop;

  return(ds->len);
}
