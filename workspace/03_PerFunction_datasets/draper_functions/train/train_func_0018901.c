obstcp_accum_commit(struct obstcp_accum *ac, ssize_t bytes) {
  struct obstcp_accum_buffer *ab = NULL;
  uint8_t c, next;
  ssize_t used = 0;

  if (bytes < 0) {
    errno = EINVAL;
    return -1;
  }

  for (c = ac->data_head; bytes && c != 0xff; c = next) {
    ab = &ac->buffers[c];

    if (ab->prefix_used < ab->prefix_len) {
      size_t a = ab->prefix_len - ab->prefix_used;
      if (a > bytes) a = bytes;
      ab->prefix_used += a;
      bytes -= a;
    }

    size_t a = ab->payload_len - ab->payload_used;
    if (a > bytes) a = bytes;
    ab->payload_used += a;
    bytes -= a;
    used += a;

    next = ab->next;

    if (ab->payload_len == ab->payload_used &&
        ab->prefix_len == ab->prefix_used) {

      ac->data_head = ab->next;
      if (ac->data_head == 0xff) ac->data_tail = 0xff;

      ab->next = ac->free_head;
      ac->free_head = c;
    }
  }


  if (bytes) {
    errno = EINVAL;
    return -1;
  }

  return used;
}
