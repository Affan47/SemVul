_hash_lookup(T_HashTable *H,T_HashTableEl *E, T_HashTableEl **E2,
			int *hint, int isIdentity)
{
  int f2, pos, upos, ttl;

  pos = H->f1(E) % H->size;
  ttl = H->size;
  f2 = -1;
  upos = -1;
  while(ttl &&
	H->entries[pos] != &unallocated &&
	(H->entries[pos] == &deleted ||
	 ((isIdentity || H->compar(H->entries[pos], E) != 0) &&
	  (!isIdentity || H->entries[pos] != E)))){
    if (f2 == -1)
      f2 = H->f2(E) % (H->size - 1);
    if (upos == -1 && H->entries[pos] == &deleted)
      upos = pos;
    pos = (pos+f2+1) % H->size;
    ttl--;
  }
  if(H->entries[pos] == &unallocated || !ttl)
    return -1;
  if (upos != -1){
    H->entries[upos] = H->entries[pos];
    H->entries[pos] = &deleted;
    pos = upos;
  }
  if(hint)
    *hint = pos;
  *E2= H->entries[pos];
  return 0;
}
