hasBlockValue(Value *Val, BasicBlock *BB) {

  if (isa<Constant>(Val))
    return true;

  LVIValueHandle ValHandle(Val, this);
  auto I = ValueCache.find(ValHandle);
  if (I == ValueCache.end()) return false;
  return I->second.count(BB);
}
