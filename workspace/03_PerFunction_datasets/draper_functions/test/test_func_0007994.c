MOV_RLIb(bxInstruction_c *i)
{
  BX_WRITE_8BIT_REGx(i->opcodeReg(), i->extend8bitL(), i->Ib());
}
