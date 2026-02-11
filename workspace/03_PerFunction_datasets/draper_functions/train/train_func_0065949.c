isLifetimeStart(const Instruction *Inst) {
  if (const IntrinsicInst* II = dyn_cast<IntrinsicInst>(Inst))
    return II->getIntrinsicID() == Intrinsic::lifetime_start;
  return false;
}
