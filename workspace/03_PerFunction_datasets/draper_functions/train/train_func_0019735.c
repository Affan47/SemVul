add(IPAddress dst, IPAddress mask, IPAddress gw, int index)
{
  dst &= mask;

  struct Entry e;
  e.dst = dst;
  e.mask = mask;
  e.gw = gw;
  e.index = index;

  for (int i = 0; i < _v.size(); i++)
    if (!_v[i].valid()) {
      _v[i] = e;
      return;
    }
  _v.push_back(e);
}
