ReceiveSessionResponse(
    const std::string& response) {

  StringMap map;
  ParseMap(response, map);

  std::string username = map["username"];
  std::string password = map["password"];
  std::string magic_cookie = map["magic_cookie"];

  std::string relay_ip = map["relay.ip"];
  std::string relay_udp_port = map["relay.udp_port"];
  std::string relay_tcp_port = map["relay.tcp_port"];
  std::string relay_ssltcp_port = map["relay.ssltcp_port"];

  PortConfiguration* config = new PortConfiguration(stun_hosts_[0],
                                                    username,
                                                    password,
                                                    magic_cookie);

  PortConfiguration::PortList ports;
  if (!relay_udp_port.empty()) {
    talk_base::SocketAddress address(relay_ip, atoi(relay_udp_port.c_str()));
    ports.push_back(ProtocolAddress(address, PROTO_UDP));
  }
  if (!relay_tcp_port.empty()) {
    talk_base::SocketAddress address(relay_ip, atoi(relay_tcp_port.c_str()));
    ports.push_back(ProtocolAddress(address, PROTO_TCP));
  }
  if (!relay_ssltcp_port.empty()) {
    talk_base::SocketAddress address(relay_ip, atoi(relay_ssltcp_port.c_str()));
    ports.push_back(ProtocolAddress(address, PROTO_SSLTCP));
  }
  config->AddRelay(ports, 0.0f);
  ConfigReady(config);
}
