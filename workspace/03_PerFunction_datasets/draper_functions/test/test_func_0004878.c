getVarDeclTypeLocBegin(const VarDecl *VD)
{
  TypeLoc VarTypeLoc = VD->getTypeSourceInfo()->getTypeLoc();

  TypeLoc NextTL = VarTypeLoc.getNextTypeLoc();
  while (!NextTL.isNull()) {
    VarTypeLoc = NextTL;
    NextTL = NextTL.getNextTypeLoc();
  }

  return VarTypeLoc.getLocStart();
}
