setFormat(int pos, int len, const QTextCharFormat &format)
{
  QMap<int,Fmt>::iterator it = formats.upperBound(pos);
  if (it != formats.end() && it.key() == pos)
    ++it;
  while (it != formats.end() && pos+len > it->pos)
    {
      if (pos > it->pos)
        {
          Fmt fmt = it.value();
          fmt.len = pos - it->pos;
          formats[fmt.len + fmt.pos] = fmt;
        }
      if (pos+len < it->pos + it->len)
        {
          int shift = pos + len - it->pos;
          it->pos += shift;
          it->len -= shift;
          ++it;
        }
      else
        {
          it = formats.erase(it);
        }
    }
  Fmt fmt;
  fmt.pos = pos;
  fmt.len = len;
  fmt.format = format;
  formats[pos + len] = fmt;
}
