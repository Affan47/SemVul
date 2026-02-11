byteReverse(unsigned char *buf, unsigned longs) {
  static const int endianess_check = 1;
  uint32_t t;
  if (((char *) &endianess_check)[0] == 1) {
    do {
      t = (uint32_t) ((unsigned) buf[3] << 8 | buf[2]) << 16 |
        ((unsigned) buf[1] << 8 | buf[0]);
      * (uint32_t *) buf = t;
      buf += 4;
    } while (--longs);
  }
}
