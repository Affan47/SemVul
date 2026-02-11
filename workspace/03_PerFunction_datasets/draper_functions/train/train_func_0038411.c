rb_write (rb_t * rb, const char *src, size_t cnt)
{
  size_t free_cnt;
  size_t cnt2;
  size_t to_write;
  size_t n1, n2;

  if ((free_cnt = rb_write_space (rb)) == 0) {
    return 0;
  }

  to_write = cnt > free_cnt ? free_cnt : cnt;

  cnt2 = rb->write_ptr + to_write;

  if (cnt2 > rb->size) {
    n1 = rb->size - rb->write_ptr;
    n2 = cnt2 & rb->size_mask;
  } else {
    n1 = to_write;
    n2 = 0;
  }

  memcpy (&(rb->buf[rb->write_ptr]), src, n1);
  rb->write_ptr += n1;
  rb->write_ptr &= rb->size_mask;

  if (n2) {
    memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
    rb->write_ptr += n2;
    rb->write_ptr &= rb->size_mask;
  }

  return to_write;
}
