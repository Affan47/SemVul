hash_add(T_HashTable *H, T_HashTableEl *E, int *hint)
{
  if (H->fill >= H->max)
    rehash(H);
  if (H->fill == H->size)
    return -1;
  return _hash_add(H,E, hint);
}
