setreg (HP4200_Scanner * s, unsigned char reg, unsigned char reg_value)
{
  s->regs[reg] = reg_value;
  if ((reg < 0x08) || (reg > 0x5b))
    {
      lm9830_write_register (s->fd, reg, reg_value);
    }
}
