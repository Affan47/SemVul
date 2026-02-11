get_configured_bridge_by_addr_port_digest(const tor_addr_t *addr,
                                          uint16_t port,
                                          const char *digest)
{
  if (!bridge_list)
    return NULL;
  SMARTLIST_FOREACH_BEGIN(bridge_list, bridge_info_t *, bridge)
    {
      if (tor_digest_is_zero(bridge->identity) &&
          !tor_addr_compare(&bridge->addr, addr, CMP_EXACT) &&
          bridge->port == port)
        return bridge;
      if (digest && tor_memeq(bridge->identity, digest, DIGEST_LEN))
        return bridge;
    }
  SMARTLIST_FOREACH_END(bridge);
  return NULL;
}
