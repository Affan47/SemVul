AddTranslator(
    const SocketAddress& ext_ip, const SocketAddress& int_ip, NATType type) {

  if (nats_.Get(ext_ip))
    return NULL;

  AddClient(ext_ip);
  return nats_.Add(ext_ip,
                   new Translator(server_, type, int_ip, server_, ext_ip));
}
