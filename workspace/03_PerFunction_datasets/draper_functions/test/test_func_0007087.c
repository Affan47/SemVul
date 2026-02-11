isInterestingPointer(Value *V) {
  return V->getType()->isPointerTy()
      && !isa<ConstantPointerNull>(V);
}
