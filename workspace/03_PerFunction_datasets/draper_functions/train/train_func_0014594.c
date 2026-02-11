skip_lws(const uint8_t ** p) {
  while (**p != '\0' && is_lws(**p)) {
    (*p)++;
  }
}
