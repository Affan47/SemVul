to_stdstring(uint32_t v)
{
  char buf[64];
  snprintf(buf, sizeof(buf), "%lu", static_cast<unsigned long>(v));
  return std::string(buf);
}
