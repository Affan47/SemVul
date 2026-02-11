OUTSB16_DXXb(bxInstruction_c *i)
{
  Bit8u value8 = read_virtual_byte_32(i->seg(), SI);
  BX_OUTP(DX, value8, 1);

  if (BX_CPU_THIS_PTR get_DF())
    SI--;
  else
    SI++;
}
