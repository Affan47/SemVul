prepare_hostname_cache_key(const char *ip_string,
                                       char *ip_key)
{
  int ip_string_length= strlen(ip_string);
  DBUG_ASSERT(ip_string_length < HOST_ENTRY_KEY_SIZE);

  memset(ip_key, 0, HOST_ENTRY_KEY_SIZE);
  memcpy(ip_key, ip_string, ip_string_length);
}
