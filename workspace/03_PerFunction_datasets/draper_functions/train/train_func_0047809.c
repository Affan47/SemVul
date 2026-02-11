ProcessStart() {
  std::vector<std::string> relay_hosts;
  std::vector<talk_base::SocketAddress> stun_hosts;
  std::string relay_token;
  const XmlElement * stanza = NextStanza();
  if (stanza == NULL)
    return STATE_BLOCKED;
  const XmlElement * query = stanza->FirstNamed(QN_JINGLE_INFO_QUERY);
  if (query == NULL)
    return STATE_START;
  const XmlElement *stun = query->FirstNamed(QN_JINGLE_INFO_STUN);
  if (stun) {
    for (const XmlElement *server = stun->FirstNamed(QN_JINGLE_INFO_SERVER);
         server != NULL; server = server->NextNamed(QN_JINGLE_INFO_SERVER)) {
      std::string host = server->Attr(QN_JINGLE_INFO_HOST);
      std::string port = server->Attr(QN_JINGLE_INFO_UDP);
      if (host != STR_EMPTY && host != STR_EMPTY) {
        stun_hosts.push_back(talk_base::SocketAddress(host, atoi(port.c_str())));
      }
    }
  }

  const XmlElement *relay = query->FirstNamed(QN_JINGLE_INFO_RELAY);
  if (relay) {
    relay_token = relay->TextNamed(QN_JINGLE_INFO_TOKEN);
    for (const XmlElement *server = relay->FirstNamed(QN_JINGLE_INFO_SERVER);
         server != NULL; server = server->NextNamed(QN_JINGLE_INFO_SERVER)) {
      std::string host = server->Attr(QN_JINGLE_INFO_HOST);
      if (host != STR_EMPTY) {
        relay_hosts.push_back(host);
      }
    }
  }
  SignalJingleInfo(relay_token, relay_hosts, stun_hosts);
  return STATE_START;
}
}
