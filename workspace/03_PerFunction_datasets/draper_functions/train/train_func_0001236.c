inc_host_errors(const char *ip_string)
{
  if (!ip_string)
    return;

  char ip_key[HOST_ENTRY_KEY_SIZE];
  prepare_hostname_cache_key(ip_string, ip_key);

  mysql_mutex_lock(&hostname_cache->lock);

  Host_entry *entry= hostname_cache_search(ip_key);

  if (entry)
    entry->connect_errors++;

  mysql_mutex_unlock(&hostname_cache->lock);
}
