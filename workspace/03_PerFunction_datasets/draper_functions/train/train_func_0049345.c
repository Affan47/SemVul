ROL_EdM(bxInstruction_c *i)
{
  Bit32u op1_32, result_32;
  unsigned count;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));


  op1_32 = read_RMW_virtual_dword(i->seg(), eaddr);

  if (i->b1() == 0xd3)
    count = CL;
  else
    count = i->Ib();

  count &= 0x1f;
  if (! count) return;

  result_32 = (op1_32 << count) | (op1_32 >> (32 - count));

  write_RMW_virtual_dword(result_32);

  unsigned bit0  = (result_32 & 0x1);
  unsigned bit31 = (result_32 >> 31);

  SET_FLAGS_OxxxxC(bit0 ^ bit31, bit0);
}
