warn_nonlocal_client_ports(const smartlist_t *ports, const char *portname)
{
  SMARTLIST_FOREACH_BEGIN(ports, const port_cfg_t *, port) {
    if (port->is_unix_addr) {

    } else if (!tor_addr_is_internal(&port->addr, 1)) {
      log_warn(LD_CONFIG, "You specified a public address for %sPort. "
               "Other people on the Internet might find your computer and "
               "use it as an open proxy. Please don't allow this unless you "
               "have a good reason.", portname);
    } else if (!tor_addr_is_loopback(&port->addr)) {
      log_notice(LD_CONFIG, "You configured a non-loopback address for "
                 "%sPort. This allows everybody on your local network to use "
                 "your machine as a proxy. Make sure this is what you wanted.",
                 portname);
    }
  } SMARTLIST_FOREACH_END(port);
}
