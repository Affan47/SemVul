hash_search( mapInfoProcessT *hash, uint32_t process)
{
  uint32_t hashkey = process;

  HASH_GET_KEY( hashkey );

  if( hash[hashkey].process == process )
  {
    return &(hash[hashkey]);
  }
  else
  {
    return search_inner( hash[hashkey].next, process );
  }
}
