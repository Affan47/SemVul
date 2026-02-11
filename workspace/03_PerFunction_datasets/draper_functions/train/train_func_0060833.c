is_text(uint8_t c) {
  return ! (c <= 31 || c == 127);
}
