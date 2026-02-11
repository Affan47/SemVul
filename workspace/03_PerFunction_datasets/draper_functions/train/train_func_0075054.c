getOrInsertGlobal(StringRef Name, const Type *Ty) {

  GlobalVariable *GV = dyn_cast_or_null<GlobalVariable>(getNamedValue(Name));
  if (GV == 0) {

    GlobalVariable *New =
      new GlobalVariable(*this, Ty, false, GlobalVariable::ExternalLinkage,
                         0, Name);
     return New;
  }


  if (GV->getType() != PointerType::getUnqual(Ty))
    return ConstantExpr::getBitCast(GV, PointerType::getUnqual(Ty));


  return GV;
}
