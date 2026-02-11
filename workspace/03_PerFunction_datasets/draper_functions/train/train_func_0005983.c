isLineTerminator()
{
  bool cr = (current == '\r');
  bool lf = (current == '\n');
  if (cr)
      skipLF = true;
  else if (lf)
      skipCR = true;
  return cr || lf || current == 0x2028 || current == 0x2029;
}
