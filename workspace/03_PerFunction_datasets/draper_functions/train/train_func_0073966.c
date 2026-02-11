restoreSocketPair(const dmtcp::vector<int>& fds,
                                             dmtcp::TcpConnection *peer,
                                             const dmtcp::vector<int>& peerfds)
{
  int sv[2];
  JASSERT(_peerType == PEER_SOCKETPAIR && _socketpairPeerId == peer->id())
    (_peerType) (_socketpairPeerId) (peer->id());
  JASSERT(fds.size() > 0);
  JASSERT(peerfds.size() > 0);

  if (_socketPairRestored) {
    _socketPairRestored = false;
    return;
  }
  JASSERT(_real_socketpair( _sockDomain,_sockType,_sockProtocol, sv) == 0)
    (JASSERT_ERRNO);

  jalib::JSocket sock1(sv[0]);
  jalib::JSocket sock2(sv[1]);

  sock1.changeFd(fds[0]);
  sock2.changeFd(peerfds[0]);

  for (size_t i=1; i<fds.size(); ++i) {
    JASSERT(_real_dup2(fds[0], fds[i]) == fds[i]) (fds[0]) (fds[i])
      .Text("dup2() failed");
  }

  for (size_t i=1; i<peerfds.size(); ++i) {
    JASSERT(_real_dup2(peerfds[0], peerfds[i]) == peerfds[i])
      (peerfds[0]) (peerfds[i]) .Text("dup2() failed");
  }
  peer->_socketPairRestored = true;
  JTRACE("Restored Socketpair") (id()) (peer->id()) (fds[0]) (peerfds[0]);
}
