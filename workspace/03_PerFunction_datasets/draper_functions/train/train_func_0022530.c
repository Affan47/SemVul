var_ns_buf(Var_ns *root, char *name)
{
  char *str;
  Kwv *kwv;

  if ((kwv = var_ns_lookup_kwv(root, name)) == NULL)
	return("");

  str = kwv_buf(kwv, '=', '"');
  return(str);
}
