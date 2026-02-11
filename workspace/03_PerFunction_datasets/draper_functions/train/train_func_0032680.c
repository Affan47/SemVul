find_constant2 (CPool *cpool, int tag, jword word1, jword word2)
{
  int i;
  for (i = cpool->count - 1;  --i > 0; )
    {
      if (cpool->tags[i] == tag
	  && cpool->data[i].w == word1
	  && cpool->data[i+1].w == word2)
	return i;
    }
  i = cpool->count == 0 ? 1 : cpool->count;
  set_constant_entry (cpool, i, tag, word1);
  set_constant_entry (cpool, i+1, 0, word2);
  return i;
}
