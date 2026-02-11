XADD_EbGbM(bxInstruction_c *i)
{
#if BX_CPU_LEVEL >= 4
  Bit8u op1, op2, sum;


  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  op1 = read_RMW_virtual_byte(i->seg(), eaddr);
  op2 = BX_READ_8BIT_REGx(i->nnn(), i->extend8bitL());
  sum = op1 + op2;
  write_RMW_virtual_byte(sum);


  BX_WRITE_8BIT_REGx(i->nnn(), i->extend8bitL(), op1);

  SET_FLAGS_OSZAPC_ADD_8(op1, op2, sum);
#else
  BX_INFO(("XADD_EbGb: not supported on < 80486"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
