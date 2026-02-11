save_gtab_buf_shift_enter()
{
  if (!ggg.gbufN)
    return 0;
  int idx0 = 0;
  if (ggg.gbufN != ggg.gbuf_cursor)
    idx0 = ggg.gbuf_cursor;
  int len = ggg.gbufN - idx0;
  if (len > MAX_PHRASE_LEN)
    return 0;

  save_gtab_buf_phrase_idx(idx0, len);
  gbuf_cursor_end();
  return 1;
}
