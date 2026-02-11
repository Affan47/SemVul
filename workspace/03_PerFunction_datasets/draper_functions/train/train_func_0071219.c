SHR_EdR(bxInstruction_c *i)
{
  Bit32u op1_32, result_32;
  unsigned count;
  unsigned of, cf;

  if (i->b1() == 0xd3)
    count = CL;
  else
    count = i->Ib();

  count &= 0x1f;
  if (!count) return;

  op1_32 = BX_READ_32BIT_REG(i->rm());
  result_32 = (op1_32 >> count);
  BX_WRITE_32BIT_REGZ(i->rm(), result_32);

  cf = (op1_32 >> (count - 1)) & 0x1;


  of = ((result_32 << 1) ^ result_32) >> 31;

  SET_FLAGS_OSZAPC_LOGIC_32(result_32);
  SET_FLAGS_OxxxxC(of, cf);
}
