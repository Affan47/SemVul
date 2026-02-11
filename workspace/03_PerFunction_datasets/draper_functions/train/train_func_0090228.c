STOSW32_YwAX(bxInstruction_c *i)
{
  Bit32u edi = EDI;

  write_virtual_word(BX_SEG_REG_ES, edi, AX);

  if (BX_CPU_THIS_PTR get_DF()) {
    edi -= 2;
  }
  else {
    edi += 2;
  }


  RDI = edi;
}
