crc32ul(const std::string & s) {
  static std::vector<unsigned long> crc_table =  gen_crc_table();
  unsigned long crc = 0;
  int end = s.length();
  for (int j = 0; j != end; ++j) {
    int i = ( (int) ( crc >> 24) ^ s[j] ) & 0xff;
    crc = ( ( crc << 8 ) ^ crc_table[i] ) & 0xffffffffUL;
  }
  return crc;
}
