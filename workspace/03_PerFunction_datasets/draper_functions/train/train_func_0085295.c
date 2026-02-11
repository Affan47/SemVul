ares_set_servers(ares_channel channel,
                     struct ares_addr_node *servers)
{
  struct ares_addr_node *srvr;
  int num_srvrs = 0;
  int i;

  if (ares_library_initialized() != ARES_SUCCESS)
    return ARES_ENOTINITIALIZED;

  if (!channel)
    return ARES_ENODATA;

  ares__destroy_servers_state(channel);

  for (srvr = servers; srvr; srvr = srvr->next)
    {
      num_srvrs++;
    }

  if (num_srvrs > 0)
    {

      channel->servers = malloc(num_srvrs * sizeof(struct server_state));
      if (!channel->servers)
        {
          return ARES_ENOMEM;
        }
      channel->nservers = num_srvrs;

      for (i = 0, srvr = servers; srvr; i++, srvr = srvr->next)
        {
          channel->servers[i].addr.family = srvr->family;
          if (srvr->family == AF_INET)
            memcpy(&channel->servers[i].addr.addrV4, &srvr->addrV4,
                   sizeof(srvr->addrV4));
          else
            memcpy(&channel->servers[i].addr.addrV6, &srvr->addrV6,
                   sizeof(srvr->addrV6));
        }

      ares__init_servers_state(channel);
    }

  return ARES_SUCCESS;
}
