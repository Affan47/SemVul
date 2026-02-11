adds(struct BufData *buf_p, int s_len, const char *s)
{
  int overflow = 0;


  while (s_len && *s)
  {

    if (buf_p->limit == 0) {
      buf_p->overflow++;
      overflow++;
    } else if (buf_p->limit > 0)
      buf_p->limit--;

    if (buf_p->buf_loc >= buf_p->buf_size) {
      buf_p->buf_overflow++;
      overflow++;
    }

    if (!overflow)
      buf_p->buf[buf_p->buf_loc++] = *s;

    s++;
    if (s_len > 0)
      s_len--;
  }
}
