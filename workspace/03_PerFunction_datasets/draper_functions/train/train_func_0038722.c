sync(unsigned int) {
  if (this->buf_free(0, 1) || flush_meta()) return (-1);
  this->new_file = 0;
  return 0;
}
