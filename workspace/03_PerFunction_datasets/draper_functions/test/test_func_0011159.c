knocker_core_resolve_host (knocker_core_portscan_data_t * data, const char *hostname, int family)
{
  if (knocker_core_gethostbyname (&data->host, hostname, family) == -1)
    return NULL;
  else
    return (data->host.ip);
}
