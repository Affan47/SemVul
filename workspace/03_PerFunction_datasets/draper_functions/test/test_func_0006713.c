validate_tunnel_info( const tTunnel* pTunnelInfo )
{
  sint32_t err_num = 0;


  if( !IsAll(IPv4Addr, pTunnelInfo->client_address_ipv4) )
  {
    Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_CLIENT_IPV4_RECVD);
    err_num++;
  }

  if( !IsAll(IPv6Addr, pTunnelInfo->client_address_ipv6) )
  {
    Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_CLIENT_IPV6_RECVD);
    err_num++;
  }

  if( pTunnelInfo->client_dns_server_address_ipv6 != NULL )
  {
    if( !IsAll(IPv6Addr, pTunnelInfo->client_dns_server_address_ipv6) )
    {
      Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_CLIENT_DNS_IPV6_RECVD);
      err_num++;
    }
  }

  if( !IsAll(IPv4Addr, pTunnelInfo->server_address_ipv4) )
  {
    Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_SERVER_IPV4_RECVD);
    err_num++;
  }

  if( !IsAll(IPv6Addr, pTunnelInfo->server_address_ipv6) )
  {
    Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_SERVER_IPV6_RECVD);
    err_num++;
  }


  if( pTunnelInfo->prefix != NULL )
  {
    if( !IsAll(IPAddrAny, pTunnelInfo->prefix) )
    {
      Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_SERVER_PREFIX_RECVD);
      err_num++;
    }

    if( !IsAll(Numeric, pTunnelInfo->prefix_length) )
    {
      Display(LOG_LEVEL_1, ELError, "validate_tunnel_info", GOGO_STR_BAD_PREFIX_LEN_RECVD);
      err_num++;
    }
  }

  return err_num;
}
