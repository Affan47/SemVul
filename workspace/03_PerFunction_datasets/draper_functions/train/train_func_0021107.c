handleOneDeclarator(const Type *Ty)
{
  const RecordDecl *RD = getBaseRecordDecl(Ty);
  if (!RD)
    return true;

  const RecordDecl *CanonicalRD = dyn_cast<RecordDecl>(RD->getCanonicalDecl());
  if (CanonicalRD == TheRecordDecl) {
    SafeToRemoveName = false;
  }
  return SafeToRemoveName;
}
