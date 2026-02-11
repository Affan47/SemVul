search_in_bucket(ght_hash_table_t *p_ht, ght_uint32_t l_bucket,
						 ght_hash_key_t *p_key, unsigned char i_heuristics)
{
  ght_hash_entry_t *p_e;

  for (p_e = p_ht->pp_entries[l_bucket];
       p_e;
       p_e = p_e->p_next)
    {
      if ((p_e->key.i_size == p_key->i_size) &&
	  (memcmp(p_e->key.p_key, p_key->p_key, p_e->key.i_size) == 0))
	{

	  switch (i_heuristics)
	    {
	    case GHT_HEURISTICS_MOVE_TO_FRONT:
	      move_to_front(p_ht, l_bucket, p_e);
	      break;
	    case GHT_HEURISTICS_TRANSPOSE:
	      transpose(p_ht, l_bucket, p_e);
	      break;
	    default:
	      break;
	    }
	  return p_e;
	}
    }
  return NULL;
}
