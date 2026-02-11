kwv_replace(Kwv *kwv, char *key, char *val)
{
  Kwv_pair pair;

  kwv_set_pair(&pair, key, val, NULL);

  if (kwv == NULL)
	return(kwv_add_pair(NULL, &pair));
  else
	return(replace(kwv, &pair, DO_COPY));
}
