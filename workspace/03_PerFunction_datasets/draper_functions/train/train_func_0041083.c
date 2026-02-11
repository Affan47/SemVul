he_display(const struct he_s *hedit, int start, int end)
{
  int i;

  if (end < 0) end = hx_lines - 2;
  if (start > end) return;
  for (i = start; i <= end; ++i) {
    tio_goto_line(i);
    tio_return();
    tio_display(he_line(hedit, hedit->screen_offset + 16 * i), 0);
    tio_clear_to_eol();
  }
  he_set_cursor(hedit);
}
