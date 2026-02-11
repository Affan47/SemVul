RCR_EdM(bxInstruction_c *i)
{
  Bit32u op1_32, result_32;
  unsigned count;
  unsigned cf, of;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));


  op1_32 = read_RMW_virtual_dword(i->seg(), eaddr);

  if (i->b1() == 0xd3)
    count = CL;
  else
    count = i->Ib();

  count &= 0x1f;
  if (!count) return;

  if (count==1) {
    result_32 = (op1_32 >> 1) | (getB_CF() << 31);
  }
  else {
    result_32 = (op1_32 >> count) | (getB_CF() << (32 - count)) |
                (op1_32 << (33 - count));
  }

  write_RMW_virtual_dword(result_32);

  cf = (op1_32 >> (count - 1)) & 0x1;
  of = ((result_32 << 1) ^ result_32) >> 31;
  SET_FLAGS_OxxxxC(of, cf);
}
