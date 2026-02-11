get_parameter(int param) const
{
  switch (param) {
  case 1:
    return gain * 100.0;
  case 2:
    return maxnum_of_clipped;
  }
  DBC_NEVER_REACHED();
  return 0.0f;
}
