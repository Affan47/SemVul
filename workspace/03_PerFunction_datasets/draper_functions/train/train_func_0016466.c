Hash(i::Vector<const byte> key, bool is_ascii) {


  int length = key.length();
  uint32_t hash = (length << 1) | (is_ascii ? 1 : 0) ;
  for (int i = 0; i < length; i++) {
    uint32_t c = key[i];
    hash = (hash + c) * 1025;
    hash ^= (hash >> 6);
  }
  return hash;
}
