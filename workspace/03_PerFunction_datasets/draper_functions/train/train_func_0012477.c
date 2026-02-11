my_hash_next(const HASH *hash, const uchar *key, size_t length,
                    HASH_SEARCH_STATE *current_record)
{
  HASH_LINK *pos;
  uint idx;

  if (*current_record != NO_RECORD)
  {
    HASH_LINK *data=dynamic_element(&hash->array,0,HASH_LINK*);
    for (idx=data[*current_record].next; idx != NO_RECORD ; idx=pos->next)
    {
      pos=data+idx;
      if (!hashcmp(hash,pos,key,length))
      {
	*current_record= idx;
	return pos->data;
      }
    }
    *current_record= NO_RECORD;
  }
  return 0;
}
