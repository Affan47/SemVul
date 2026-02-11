str2Address(const char* address) {

  const char* param;
  giopTransportImpl* impl = matchType(address,param,1);
  if (impl) {
    return impl->toAddress(param);
  }
  return 0;
}
