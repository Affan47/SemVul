rfind(const UString &f, int pos) const
{
  int sz = size();
  int fsz = f.size();
  if (sz < fsz)
    return -1;
  if (pos < 0)
    pos = 0;
  if (pos > sz - fsz)
    pos = sz - fsz;
  if (fsz == 0)
    return pos;
  int fsizeminusone = (fsz - 1) * sizeof(UChar);
  const UChar *fdata = f.data();
  const UChar* data_ = data();
  for (const UChar* c = data_ + pos; c >= data_; c--) {
    if (*c == *fdata && !memcmp(c + 1, fdata + 1, fsizeminusone))
      return (c - data_);
  }

  return -1;
}
