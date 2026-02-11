find_cidr6(struct s_whois_query *wq, const char *block)
{
  struct in6_addr query_ip;
  struct in6_addr entry_ip;
  struct jconfig *j;
  unsigned int max_bits, bits, match_bits;
  int res;
  char *p, *addr, *host = NULL;

  p = strchr(wq->query, '/');
  if (p == NULL)
    {
      addr = strdup(wq->query);
      max_bits = 128;
    }
  else
    {
      size_t len;

      if (sscanf(p + 1, "%u", &max_bits) != 1)
	return NULL;
      len = p - wq->query;
      addr = malloc(len + 1);
      memcpy(addr, wq->query, len);
      addr[len] = '\0';
    }
  res = inet_pton(AF_INET6, addr, &query_ip);
  free(addr);
  if (res != 1)
    return NULL;

  match_bits = 0;

  jconfig_set();
  while ((j = jconfig_next(block)) != NULL)
    {
      if (strcasecmp(j->key, "type") == 0)
	continue;
      if (!strcasecmp(j->key, "default"))
	{
	  memset(entry_ip.s6_addr, 0, sizeof(entry_ip.s6_addr));
	  bits = 0;
	}
      else
	{
	  size_t len;

	  p = strchr(j->key, '/');
	  if (p == NULL)
	    {
	      printf(_("[%s: Missing prefix length on line %d]\n"),
		     config, j->line);
	      continue;
	    }
	  if (sscanf(p + 1, "%u", &bits) != 1 || bits > 128)
	    {
	      printf(_("[%s: Invalid prefix length on line %d]\n"), config,
		     j->line);
	      continue;
	    }
	  len = p - j->key;
	  addr = malloc(len + 1);
	  memcpy(addr, j->key, len);
	  addr[len] = '\0';
	  res = inet_pton(AF_INET6, addr, &entry_ip);
	  free(addr);
	  if (res != 1)
	    {
	      printf(_("[%s: Invalid network address on line %d]\n"), config,
		     j->line);
	      continue;
	    }
	}
      if (ipv6_address_is_in_network(&query_ip, &entry_ip, bits)
	  && bits <= max_bits && bits >= match_bits)
	{
	  host = j->value;
	  match_bits = bits;
	}
    }
  jconfig_end();

  return host;
}
