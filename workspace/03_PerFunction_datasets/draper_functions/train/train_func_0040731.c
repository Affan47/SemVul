OUTSW16_DXXw(bxInstruction_c *i)
{
  Bit16u value16 = read_virtual_word_32(i->seg(), SI);
  BX_OUTP(DX, value16, 2);

  if (BX_CPU_THIS_PTR get_DF())
    SI -= 2;
  else
    SI += 2;
}
