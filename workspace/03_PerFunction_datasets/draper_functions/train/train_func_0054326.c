LoadWord (ARMul_State * state, ARMword instr, ARMword address)
{
  ARMword dest;

  BUSUSEDINCPCS;
#ifndef MODE32
  if (ADDREXCEPT (address))
    INTERNALABORT (address);
#endif

  dest = ARMul_LoadWordN (state, address);

  if (state->Aborted)
    {
      TAKEABORT;
      return state->lateabtSig;
    }
  if (address & 3)
    dest = ARMul_Align (state, address, dest);
  WRITEDESTB (dest);
  ARMul_Icycles (state, 1, 0L);

  return (DESTReg != LHSReg);
}
