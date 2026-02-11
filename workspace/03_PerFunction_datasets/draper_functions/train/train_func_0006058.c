invalidate_table_internal(THD *thd, uchar *key, uint32 key_length)
{
  Query_cache_block *table_block=
    (Query_cache_block*)my_hash_search(&tables, key, key_length);
  if (table_block)
  {
    Query_cache_block_table *list_root= table_block->table(0);
    invalidate_query_block_list(thd, list_root);
  }
}
