GetConnection(int connection) const {
  int i = 0;
  for (ConnectionMap::const_iterator it = connections_.begin();
       it != connections_.end(); ++it) {
    if (i == connection) {
      return it->second->addr_pair();
    }
    ++i;
  }
  return talk_base::SocketAddressPair();
}
