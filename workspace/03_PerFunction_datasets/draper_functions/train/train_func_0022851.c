varint_put(uint8_t *out, unsigned length, unsigned *offset, unsigned v) {
  do {
    if (*offset >= length) return 0;
    if (v > 127) {
      out[*offset] = 0x80 | (v & 0x7f);
    } else {
      out[*offset] = v;
    }

    v >>= 7;
    (*offset)++;
  } while (v);

  return 1;
}
