JNLE_Jd(bxInstruction_c *i)
{
  if (! get_ZF() && (getB_SF() == getB_OF())) {
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
