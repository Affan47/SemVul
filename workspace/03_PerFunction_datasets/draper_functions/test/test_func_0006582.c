isRefToTheSameVar(const Expr *CopyE,
                                        const Expr *DominatedE)
{
  const VarDecl *CopyVD  = getCanonicalRefVarDecl(CopyE);
  if (!CopyVD)
    return false;
  const VarDecl *DominatedVD  = getCanonicalRefVarDecl(DominatedE);
  if (!DominatedVD)
    return false;

  return (CopyVD == DominatedVD);
}
