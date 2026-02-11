ds_concat(Ds *ds, char *str)
{
  size_t len;

  len = strlen(str) + 1;
  if (ds->len == 0)
	return(ds_copyb(ds, str, len, 0));
  return(ds_copyb(ds, str, len, ds->len - 1));
}
