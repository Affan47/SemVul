prev(int __val) const
{
  if (__val >= inf() && __val <= sup())
  {
    int __idx = __val - _offset;
    int __prev = _repr.prev_set(__idx);
    if (__prev != -1)
      return __prev+_offset;
  }
  return INT_MIN;
}
