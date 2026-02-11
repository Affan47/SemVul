clearbits (HP4200_Scanner * s, unsigned char reg, unsigned char mask)
{
  s->regs[reg] = (s->regs[reg] & ~mask) & 0xff;
  if ((reg < 0x08) || (reg > 0x5b))
    {
      lm9830_write_register (s->fd, reg, LOBYTE (s->regs[reg]));
    }
}
