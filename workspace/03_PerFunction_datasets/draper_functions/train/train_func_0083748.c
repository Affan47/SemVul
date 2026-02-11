wbt200_process_data(struct read_state *pst, int fmt)
{
  char buf[RECLEN_MAX];
  size_t reclen = fmt_version[fmt].reclen;

  buf_rewind(&pst->data);

  db(2, "Processing %lu bytes of data using format %d\n", pst->data.used, fmt);

  for (;;) {
    size_t got = buf_read(&pst->data, buf, reclen);
    if (got != reclen) {
      break;
    }
    wbt200_data_chunk(pst, buf, fmt);
  }
}
