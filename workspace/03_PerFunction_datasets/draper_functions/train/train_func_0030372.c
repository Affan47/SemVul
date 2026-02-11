address_is_in_virtual_range(const char *address)
{
  struct in_addr in;
  tor_assert(address);
  if (!strcasecmpend(address, ".virtual")) {
    return 1;
  } else if (tor_inet_aton(address, &in)) {
    uint32_t addr = ntohl(in.s_addr);
    if (!addr_mask_cmp_bits(addr, virtual_addr_network,
                            virtual_addr_netmask_bits))
      return 1;
  }
  return 0;
}
