hex2bytes(uint8_t *bytes, const char *hex, int length) {
   while (length-- > 0) {
      *bytes = 0;
      if (isxdigit(hex[0]) && isxdigit(hex[1])) {
	  *bytes = xdig2num(hex[0]) * 16 + xdig2num(hex[1]);
	  hex += 2;
      }
      bytes++;
   }
}
