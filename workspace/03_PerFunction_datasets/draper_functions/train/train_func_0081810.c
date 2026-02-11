htab_create_alloc (size_t size, htab_hash hash_f, htab_eq eq_f,
                   htab_del del_f, htab_alloc alloc_f, htab_free free_f)
{
  htab_t result;
  unsigned int size_prime_index;

  size_prime_index = higher_prime_index (size);
  size = prime_tab[size_prime_index].prime;

  result = (htab_t) (*alloc_f) (1, sizeof (struct htab));
  if (result == NULL)
    return NULL;
  result->entries = (PTR *) (*alloc_f) (size, sizeof (PTR));
  if (result->entries == NULL)
    {
      if (free_f != NULL)
	(*free_f) (result);
      return NULL;
    }
  result->size = size;
  result->size_prime_index = size_prime_index;
  result->hash_f = hash_f;
  result->eq_f = eq_f;
  result->del_f = del_f;
  result->alloc_f = alloc_f;
  result->free_f = free_f;
  return result;
}
