JECXZ_Jb(bxInstruction_c *i)
{

  BX_ASSERT(i->as64L() == 0);

  Bit32u temp_ECX;

  if (i->as32L())
    temp_ECX = ECX;
  else
    temp_ECX = CX;

  if (temp_ECX == 0) {
    Bit32u new_EIP = EIP + (Bit32s) i->Id();
    branch_near32(new_EIP);
    BX_INSTR_CNEAR_BRANCH_TAKEN(BX_CPU_ID, new_EIP);
  }
#if BX_INSTRUMENTATION
  else {
    BX_INSTR_CNEAR_BRANCH_NOT_TAKEN(BX_CPU_ID);
  }
#endif
}
