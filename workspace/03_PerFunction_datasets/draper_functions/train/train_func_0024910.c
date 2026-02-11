init_query_stats_cache()
{
  query_stats_reader = 0;
  query_stats_cache_count = 0;
  if (my_hash_init_extra2(&query_stats_cache, 512, system_charset_info,
                          max_connections, 0 , 0 ,
                          (my_hash_get_key)get_query_stats_key,
                          (my_hash_free_key)free_query_stats,
                          (my_hash_get_key_hash)get_query_stats_hash,
                          HASH_KEEP_HASH))
  {
    sql_print_error("Failed to initialize query_stats_cache.");
    abort();
  }
}
