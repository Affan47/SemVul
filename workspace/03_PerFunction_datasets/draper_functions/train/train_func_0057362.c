NEG_EbR(bxInstruction_c *i)
{
  Bit8u op1_8 = BX_READ_8BIT_REGx(i->rm(), i->extend8bitL());
  op1_8 = - (Bit8s)(op1_8);
  BX_WRITE_8BIT_REGx(i->rm(), i->extend8bitL(), op1_8);

  SET_FLAGS_OSZAPC_RESULT_8(op1_8, BX_LF_INSTR_NEG8);
}
