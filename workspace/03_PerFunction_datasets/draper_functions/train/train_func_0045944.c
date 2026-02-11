HasCatchAllInSelector(IntrinsicInst *II) {
  if (!EHCatchAllValue) return false;

  unsigned ArgIdx = II->getNumArgOperands() - 1;
  GlobalVariable *GV = dyn_cast<GlobalVariable>(II->getArgOperand(ArgIdx));
  return GV == EHCatchAllValue;
}
