chash_get(chash * hash,
	      chashdatum * key, chashdatum * result)
{
  unsigned int func;
  chashiter * iter;

  func = chash_func(key->data, key->len);


  iter = hash->cells[func % hash->size];
  while (iter) {
    if (iter->key.len == key->len && iter->func == func
	&& !memcmp(iter->key.data, key->data, key->len)) {
      * result = iter->value;

      return 0;
    }
    iter = iter->next;
  }

  return -1;
}
