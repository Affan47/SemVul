in(word_t addr)
{
  byte_t ret = 0xff;

  switch (addr & 7)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      _addr = (_addr & 0xffff) | ((addr & 3) << 16);
      ret = _ram[_addr];
      _addr = (_addr & 0xff00) | (((_addr & 0xff) + 1) & 0xff);
      break;
    default:
      break;
    }

  return ret;
}
