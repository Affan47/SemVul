isValidRewrite(Value *FromVal, Value *ToVal) {


  Value *FromPtr = FromVal;
  Value *ToPtr = ToVal;
  if (GEPOperator *GEP = dyn_cast<GEPOperator>(FromVal)) {
    FromPtr = GEP->getPointerOperand();
  }
  if (GEPOperator *GEP = dyn_cast<GEPOperator>(ToVal)) {
    ToPtr = GEP->getPointerOperand();
  }
  if (FromPtr != FromVal || ToPtr != ToVal) {

    if (FromPtr == ToPtr)
      return true;


    const SCEV *FromBase = SE->getPointerBase(SE->getSCEV(FromPtr));
    const SCEV *ToBase = SE->getPointerBase(SE->getSCEV(ToPtr));
    if (FromBase == ToBase)
      return true;

    DEBUG(dbgs() << "INDVARS: GEP rewrite bail out "
          << *FromBase << " != " << *ToBase << "\n");

    return false;
  }
  return true;
}
