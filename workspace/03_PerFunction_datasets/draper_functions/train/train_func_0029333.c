word32tobytes (const WORD32 *input, char *output) {
  int j = 0;
  while (j<4*4) {
    WORD32 v = *input++;
    output[j++] = (char)(v & 0xff); v >>= 8;
    output[j++] = (char)(v & 0xff); v >>= 8;
    output[j++] = (char)(v & 0xff); v >>= 8;
    output[j++] = (char)(v & 0xff);
  }
}
