chash_next(chash * hash, chashiter * iter) {
  unsigned int indx;

  if (!iter)
    return NULL;

  indx = iter->func % hash->size;
  iter = iter->next;

  while(!iter) {
    indx++;
    if (indx >= hash->size)
      return NULL;
    iter = hash->cells[indx];
  }
  return iter;
}
