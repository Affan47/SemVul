VisitCallExpr(CallExpr *CE)
{
  const FunctionDecl *FD = CE->getDirectCallee();
  if (!FD)
    return true;

  unsigned NumParams = FD->getNumParams();
  if (NumParams != 0)
    return true;

  for (CallExpr::arg_iterator I = CE->arg_begin(),
       E = CE->arg_end(); I != E; ++I) {
    const Expr *Arg = (*I);
    const UnaryOperator *UO = dyn_cast<UnaryOperator>(Arg);
    if (!UO || (UO->getOpcode() != UO_AddrOf))
      continue;
    handleOneAddrTakenOp(UO);
  }
  return true;
}
