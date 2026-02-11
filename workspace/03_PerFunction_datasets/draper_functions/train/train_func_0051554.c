addr_port_lookup(int severity, const char *addrport, char **address,
                uint32_t *addr, uint16_t *port_out)
{
  const char *colon;
  char *_address = NULL;
  int _port;
  int ok = 1;

  tor_assert(addrport);

  colon = strrchr(addrport, ':');
  if (colon) {
    _address = tor_strndup(addrport, colon-addrport);
    _port = (int) tor_parse_long(colon+1,10,1,65535,NULL,NULL);
    if (!_port) {
      log_fn(severity, LD_GENERAL, "Port %s out of range", escaped(colon+1));
      ok = 0;
    }
    if (!port_out) {
      char *esc_addrport = esc_for_log(addrport);
      log_fn(severity, LD_GENERAL,
             "Port %s given on %s when not required",
             escaped(colon+1), esc_addrport);
      tor_free(esc_addrport);
      ok = 0;
    }
  } else {
    _address = tor_strdup(addrport);
    _port = 0;
  }

  if (addr) {

    if (tor_lookup_hostname(_address,addr)) {
      log_fn(severity, LD_NET, "Couldn't look up %s", escaped(_address));
      ok = 0;
      *addr = 0;
    }
  }

  if (address && ok) {
    *address = _address;
  } else {
    if (address)
      *address = NULL;
    tor_free(_address);
  }
  if (port_out)
    *port_out = ok ? ((uint16_t) _port) : 0;

  return ok ? 0 : -1;
}
