isCXXMemberExpr(const MemberExpr *ME)
{
  const ValueDecl *VD = ME->getMemberDecl();
  if (dyn_cast<CXXMethodDecl>(VD))
    return true;

  const FieldDecl *FD = dyn_cast<FieldDecl>(VD);
  TransAssert(FD && "Bad FieldDecl!");
  const CXXRecordDecl *CXXRD = dyn_cast<CXXRecordDecl>(FD->getParent());
  if (!CXXRD)
    return false;

  return !(CXXRD->isCLike());
}
