AddBit(int bit,
                   unsigned char* bp, unsigned char** out, size_t* outsize) {
  if (((*bp) & 7) == 0) ZOPFLI_APPEND_DATA(0, out, outsize);
  (*out)[*outsize - 1] |= bit << ((*bp) & 7);
  (*bp)++;
}
