move_to_front(ght_hash_table_t *p_ht, ght_uint32_t l_bucket, ght_hash_entry_t *p_entry)
{


  if (p_entry == p_ht->pp_entries[l_bucket])
    {
      return;
    }


  p_entry->p_prev->p_next = p_entry->p_next;
  if (p_entry->p_next)
    {
      p_entry->p_next->p_prev = p_entry->p_prev;
    }


  p_entry->p_next = p_ht->pp_entries[l_bucket];
  p_entry->p_prev = NULL;
  p_ht->pp_entries[l_bucket]->p_prev = p_entry;
  p_ht->pp_entries[l_bucket] = p_entry;
}
