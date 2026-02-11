get_interface_address(int severity, uint32_t *addr)
{
  tor_addr_t local_addr;
  int r;

  r = get_interface_address6(severity, AF_INET, &local_addr);
  if (r>=0)
    *addr = tor_addr_to_ipv4h(&local_addr);
  return r;
}
