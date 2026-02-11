ssh_string_fill(struct ssh_string_struct *s, const void *data, size_t len) {
  if ((s == NULL) || (data == NULL) ||
      (len == 0) || (len > ssh_string_len(s))) {
    return -1;
  }

  memcpy(s->data, data, len);

  return 0;
}
