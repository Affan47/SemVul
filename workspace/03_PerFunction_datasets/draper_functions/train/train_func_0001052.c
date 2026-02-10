prev_char_clipped(int pos) const
{
  if (pos<=0)
    return 0;

  IS_UTF8_ALIGNED2(this, (pos))

  char c;
  do {
    pos--;
    if (pos==0)
      return 0;
    c = byte_at(pos);
  } while ( (c&0xc0) == 0x80);

  IS_UTF8_ALIGNED2(this, (pos))
  return pos;
}
