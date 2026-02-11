VisitVarDecl(VarDecl *VD)
{
  if (ConsumerInstance->CombinedVars.count(VD))
    return true;

  const Type *T = VD->getType().getTypePtr();
  return ConsumerInstance->handleOneDeclarator(T);
}
