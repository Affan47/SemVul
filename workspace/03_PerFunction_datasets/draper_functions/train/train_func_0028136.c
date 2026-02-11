iso9660_is_achar (int c)
{
  if (!IN (c, 0x20, 0x5f)
      || IN (c, 0x23, 0x24)
      || c == 0x40
      || IN (c, 0x5b, 0x5e))
    return false;

  return true;
}
