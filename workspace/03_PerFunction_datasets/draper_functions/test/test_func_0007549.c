GetVal(unsigned ID, Type *Ty,
                                          LocTy Loc) {

  Value *Val = ID < NumberedVals.size() ? NumberedVals[ID] : 0;


  if (Val == 0) {
    std::map<unsigned, std::pair<Value*, LocTy> >::iterator
      I = ForwardRefValIDs.find(ID);
    if (I != ForwardRefValIDs.end())
      Val = I->second.first;
  }


  if (Val) {
    if (Val->getType() == Ty) return Val;
    if (Ty->isLabelTy())
      P.Error(Loc, "'%" + Twine(ID) + "' is not a basic block");
    else
      P.Error(Loc, "'%" + Twine(ID) + "' defined with type '" +
              getTypeString(Val->getType()) + "'");
    return 0;
  }

  if (!Ty->isFirstClassType() && !Ty->isLabelTy()) {
    P.Error(Loc, "invalid use of a non-first-class type");
    return 0;
  }


  Value *FwdVal;
  if (Ty->isLabelTy())
    FwdVal = BasicBlock::Create(F.getContext(), "", &F);
  else
    FwdVal = new Argument(Ty);

  ForwardRefValIDs[ID] = std::make_pair(FwdVal, Loc);
  return FwdVal;
}
