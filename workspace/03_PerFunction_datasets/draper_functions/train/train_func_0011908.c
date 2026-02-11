getRepRegClassFor(MVT VT) const {
  if (VT == MVT::Untyped)
    return Subtarget.hasDSP() ? &Mips::ACC64DSPRegClass : &Mips::ACC64RegClass;

  return TargetLowering::getRepRegClassFor(VT);
}
