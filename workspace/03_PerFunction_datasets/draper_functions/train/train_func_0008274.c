HexEncode(unsigned char *md_value,
                      int md_len,
                      char** md_hexdigest,
                      int* md_hex_len) {
  *md_hex_len = (2*(md_len));
  *md_hexdigest = new char[*md_hex_len + 1];

  char* buff = *md_hexdigest;
  const int len = *md_hex_len;
  for (int i = 0; i < len; i += 2) {

    const int index = i / 2;
    const char msb = (md_value[index] >> 4) & 0x0f;
    const char lsb = md_value[index] & 0x0f;

    buff[i] = (msb < 10) ? msb + '0' : (msb - 10) + 'a';
    buff[i + 1] = (lsb < 10) ? lsb + '0' : (lsb - 10) + 'a';
  }

  buff[*md_hex_len] = '\0';
}
