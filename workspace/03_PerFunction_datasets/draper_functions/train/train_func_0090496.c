getSupportedHashTypeString()
{
  auto ht = getSupportedHashTypes();
  std::stringstream ss;
  std::copy(std::begin(ht), std::end(ht),
            std::ostream_iterator<std::string>(ss, ", "));
  auto res = ss.str();
  if(!res.empty()) {
    res.erase(ss.str().length()-2);
  }
  return res;
}
