kwv_count(Kwv *kwv, char *key)
{
  int n;
  unsigned int slot;
  Kwv_pair *av;

  if (kwv == NULL)
	return(0);

  kwv->error_msg = NULL;
  if (kwv->npairs == 0)
    return(0);

  if (key == NULL)
    return(kwv->npairs);

  if (lookup_key(kwv, key, &slot) == 0)
	return(0);

  n = 1;
  for (av = kwv->pairs[slot]->next; av != NULL; av = av->next)
	n++;

  return(n);
}
