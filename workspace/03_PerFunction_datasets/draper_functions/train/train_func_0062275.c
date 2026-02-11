VisitVarDecl(VarDecl *VD)
{
  if (VD->isReferenced() || dyn_cast<ParmVarDecl>(VD) ||
      VD->isStaticDataMember())
    return true;

  SourceRange VarRange = VD->getSourceRange();
  if (VarRange.getEnd().isInvalid())
    return true;

  if (ConsumerInstance->SkippedVars.count(VD->getCanonicalDecl()))
    return true;

  ConsumerInstance->ValidInstanceNum++;
  if (ConsumerInstance->ValidInstanceNum ==
      ConsumerInstance->TransformationCounter) {
    ConsumerInstance->TheVarDecl = VD;
  }
  return true;
}
