AddTranslator(
    const SocketAddress& ext_ip, const SocketAddress& int_ip, NATType type) {

  if (nats_.Get(ext_ip))
    return NULL;

  return nats_.Add(ext_ip, new Translator(this, type, int_ip, server_, ext_ip));
}
