RCL_Eb(bxInstruction_c *i)
{
  Bit8u op1_8, result_8;
  unsigned count;
  unsigned of, cf;

  if (i->b1() == 0xd2)
    count = CL;
  else
    count = i->Ib();


  if (i->modC0()) {
    op1_8 = BX_READ_8BIT_REGx(i->rm(), i->extend8bitL());
  }
  else {
    bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

    op1_8 = read_RMW_virtual_byte(i->seg(), eaddr);
  }

  count = (count & 0x1f) % 9;

  if (! count) return;

  if (count==1) {
    result_8 = (op1_8 << 1) | getB_CF();
  }
  else {
    result_8 = (op1_8 << count) | (getB_CF() << (count - 1)) |
               (op1_8 >> (9 - count));
  }


  if (i->modC0()) {
    BX_WRITE_8BIT_REGx(i->rm(), i->extend8bitL(), result_8);
  }
  else {
    write_RMW_virtual_byte(result_8);
  }

  cf = (op1_8 >> (8 - count)) & 0x01;
  of = cf ^ (result_8 >> 7);
  SET_FLAGS_OxxxxC(of, cf);
}
