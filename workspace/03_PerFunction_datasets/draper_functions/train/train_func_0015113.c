HandleTopLevelDecl(DeclGroupRef DGR)
{
  DeclGroupRef::iterator DI = DGR.begin();
  const RecordDecl *RD = dyn_cast<RecordDecl>(*DI);
  if (RD) {
    addOneRecordDecl(RD, DGR);
    return true;
  }

  VarDecl *VD = dyn_cast<VarDecl>(*DI);
  if (!VD)
    return true;

  const Type *T = VD->getType().getTypePtr();

  RD = getBaseRecordDecl(T);
  if (!RD)
    return true;

  const Decl *CanonicalD = RD->getCanonicalDecl();
  void *DGRPointer = RecordDeclToDeclGroup[CanonicalD];
  if (!DGRPointer)
    return true;

  ValidInstanceNum++;
  if (ValidInstanceNum != TransformationCounter)
    return true;

  TheRecordDecl = dyn_cast<RecordDecl>(CanonicalD);
  TheDeclGroupRefs.push_back(DGRPointer);
  TheDeclGroupRefs.push_back(DGR.getAsOpaquePtr());

  for (DeclGroupRef::iterator I = DGR.begin(), E = DGR.end(); I != E; ++I) {
    VarDecl *VD = dyn_cast<VarDecl>(*I);
    TransAssert(VD && "Bad VarDecl!");
    CombinedVars.insert(VD);
  }

  DeclGroupRef DefDGR = DeclGroupRef::getFromOpaquePtr(DGRPointer);
  for (DeclGroupRef::iterator I = DefDGR.begin(),
       E = DefDGR.end(); I != E; ++I) {
    VarDecl *VD = dyn_cast<VarDecl>(*I);
    if (VD)
      CombinedVars.insert(VD);
  }
  return true;
}
