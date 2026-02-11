find_listener(int port, const struct irc_in_addr *addr)
{
  struct Listener* listener;
  for (listener = ListenerPollList; listener; listener = listener->next) {
    if (port == listener->addr.port && !memcmp(addr, &listener->addr.addr, sizeof(*addr)))
      return listener;
  }
  return 0;
}
