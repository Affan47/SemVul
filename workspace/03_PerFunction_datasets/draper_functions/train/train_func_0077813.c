Get(
    const SocketAddress& ext_ip) {
  TranslatorMap::iterator it = find(ext_ip);
  return (it != end()) ? it->second : NULL;
}
