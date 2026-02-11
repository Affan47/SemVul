buffer_add_buffer(struct ssh_buffer_struct *buffer,
    struct ssh_buffer_struct *source) {
  if (buffer_add_data(buffer, buffer_get_rest(source), buffer_get_rest_len(source)) < 0) {
    return -1;
  }

  return 0;
}
