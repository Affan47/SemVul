getSupportedHashTypes()
{
  std::vector<std::string> rv;
  for (const auto& i : hashTypes) {
    if (MessageDigestImpl::supports(i.hashType)) {
      rv.push_back(i.hashType);
    }
  }
  return rv;
}
