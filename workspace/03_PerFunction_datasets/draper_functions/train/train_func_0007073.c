do_mini_right_shift(decimal_t *dec, int shift, int beg, int last)
{
  dec1 *from= dec->buf + ROUND_UP(last) - 1;
  dec1 *end= dec->buf + ROUND_UP(beg + 1) - 1;
  int c_shift= DIG_PER_DEC1 - shift;
  DBUG_ASSERT(from < dec->buf + dec->len);
  DBUG_ASSERT(end >= dec->buf);
  if (DIG_PER_DEC1 - ((last - 1) % DIG_PER_DEC1 + 1) < shift)
    *(from + 1)= (*from % powers10[shift]) * powers10[c_shift];
  for(; from > end; from--)
    *from= (*from / powers10[shift] +
            (*(from - 1) % powers10[shift]) * powers10[c_shift]);
  *from= *from / powers10[shift];
}
