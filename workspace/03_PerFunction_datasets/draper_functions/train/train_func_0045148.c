visitLoadInst(LoadInst &I) {

  if (I.getType()->isStructTy())
    return markAnythingOverdefined(&I);

  LatticeVal PtrVal = getValueState(I.getOperand(0));
  if (PtrVal.isUndefined()) return;

  LatticeVal &IV = ValueState[&I];
  if (IV.isOverdefined()) return;

  if (!PtrVal.isConstant() || I.isVolatile())
    return markOverdefined(IV, &I);

  Constant *Ptr = PtrVal.getConstant();


  if (isa<ConstantPointerNull>(Ptr) && I.getPointerAddressSpace() == 0)
    return markConstant(IV, &I, UndefValue::get(I.getType()));


  if (GlobalVariable *GV = dyn_cast<GlobalVariable>(Ptr)) {
    if (!TrackedGlobals.empty()) {

      DenseMap<GlobalVariable*, LatticeVal>::iterator It =
        TrackedGlobals.find(GV);
      if (It != TrackedGlobals.end()) {
        mergeInValue(IV, &I, It->second);
        return;
      }
    }
  }


  if (Constant *C = ConstantFoldLoadFromConstPtr(Ptr, DL))
    return markConstant(IV, &I, C);


  markOverdefined(IV, &I);
}
