guid2string(uint64_t guid, int unit=-1) {
  std::string result;
  char buf[64];
  uint32_t value[2];

  value[0]= guid & 0xffffffff;
  value[1]= (guid >>32) & 0xffffffff;

  snprintf(buf, 64, "0x%08x%08x", value[0], value[1]);
  buf[63]=0;
  result=buf;

  if(unit>=0) {
    snprintf(buf, 64, "%d", unit);
    buf[63]=0;
    result+=":";
    result+=buf;
  }

  return result;
}
