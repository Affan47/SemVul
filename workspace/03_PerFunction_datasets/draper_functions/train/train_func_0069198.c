flush_and_reset_buffered_writes(SquatWriteBuffer* b) {
  if (b->data_len > 0) {
    if (write(b->fd, b->buf, b->data_len) != b->data_len) {
      squat_set_last_error(SQUAT_ERR_SYSERR);
      return SQUAT_ERR;
    }
    b->data_len = 0;
  }

  if (lseek(b->fd, 0, SEEK_SET) != 0) {
    squat_set_last_error(SQUAT_ERR_SYSERR);
    return SQUAT_ERR;
  }

  return SQUAT_OK;
}
