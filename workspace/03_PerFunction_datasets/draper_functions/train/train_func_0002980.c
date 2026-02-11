readInteger(const char*&At, const char*End) {
  unsigned Shift = 0;
  unsigned Result = 0;

  do {
    if (At == End)
      return Result;
    Result |= (unsigned)((*At++) & 0x7F) << Shift;
    Shift += 7;
  } while (At[-1] & 0x80);
  return Result;
}
