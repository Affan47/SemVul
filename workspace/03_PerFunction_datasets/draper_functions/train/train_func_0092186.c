hpairnode_copy(const hpair_t * src)
{
  hpair_t *pair;

  if (src == NULL)
    return NULL;

  pair = hpairnode_new(src->key, src->value, NULL);
  return pair;
}
