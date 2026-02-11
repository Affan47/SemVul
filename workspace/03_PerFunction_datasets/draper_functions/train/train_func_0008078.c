INSW16_YwDX(bxInstruction_c *i)
{

  Bit16u value16 = read_RMW_virtual_word_32(BX_SEG_REG_ES, DI);

  value16 = BX_INP(DX, 2);

  write_RMW_virtual_word(value16);

  if (BX_CPU_THIS_PTR get_DF())
    DI -= 2;
  else
    DI += 2;
}
