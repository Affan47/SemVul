conf_dns_lookup(struct AccessItem *aconf)
{
  if (!aconf->dns_pending)
  {
    aconf->dns_pending = 1;
    gethost_byname(conf_dns_callback, aconf, aconf->host);
  }
}
