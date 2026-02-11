find_all_matches(HashTable *ht, const char *str, uint length,
			 uint *res_length)
{
  Bucket *b;

  b = completion_hash_find(ht,str,length);
  if (!b) {
    *res_length = 0;
    return (Bucket*) 0;
  } else {
    *res_length = length;
    return b;
  }
}
