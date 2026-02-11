kwv_dups(Kwv *kwv, char *key)
{
  unsigned int slot;

  if (kwv == NULL || key == NULL)
	return(0);

  kwv->error_msg = NULL;
  if (kwv->npairs == 0)
    return(0);

  if (lookup_key(kwv, key, &slot) == 0)
	return(0);

  if (kwv->pairs[slot]->next != NULL)
	return(1);

  return(0);
}
