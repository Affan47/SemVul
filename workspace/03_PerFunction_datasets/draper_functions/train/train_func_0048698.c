ne_hash_init (NE_HASH **hash, NE_HASH_FUNC hash_func, NE_COMP_FUNC comp_func)
{
  NE_HASH *my_hash = NULL;

  my_hash = (NE_HASH *) calloc(1, sizeof(NE_HASH));
  if (my_hash == NULL)
    return nerr_raise(NERR_NOMEM, "Unable to allocate memory for NE_HASH");

  my_hash->size = 256;
  my_hash->num = 0;
  my_hash->hash_func = hash_func;
  my_hash->comp_func = comp_func;

  my_hash->nodes = (NE_HASHNODE **) calloc (my_hash->size, sizeof(NE_HASHNODE *));
  if (my_hash->nodes == NULL)
  {
    free(my_hash);
    return nerr_raise(NERR_NOMEM, "Unable to allocate memory for NE_HASHNODES");
  }

  *hash = my_hash;

  return STATUS_OK;
}
