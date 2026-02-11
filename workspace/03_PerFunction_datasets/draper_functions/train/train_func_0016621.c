kwv_lookup_value(Kwv *kwv, char *key)
{
  unsigned int slot;
  Kwv_pair *s;

  if (kwv == NULL)
	return(NULL);
  kwv->error_msg = NULL;
  if (lookup_key(kwv, key, &slot) == 0)
	return(NULL);

  s = kwv->pairs[slot];


  if (s == NULL || s->val == NULL || s->val[0] == '\0')
	return(NULL);

  return(s->val);
}
