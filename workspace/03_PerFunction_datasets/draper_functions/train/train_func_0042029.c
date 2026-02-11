rewriteArrayVarDecl(void)
{
  const Type *Ty = TheVarDecl->getType().getTypePtr();
  const ArrayType *ArrayTy = dyn_cast<ArrayType>(Ty);
  TransAssert(ArrayTy && "Invalid ArrayType!");
  unsigned int Dim = getArrayDimension(ArrayTy);
  TransAssert((Dim > TheDimIdx) && "Bad Dimension Index!");

  const VarDecl *FirstVD = TheVarDecl->getCanonicalDecl();
  for(VarDecl::redecl_iterator RI = FirstVD->redecls_begin(),
      RE = FirstVD->redecls_end(); RI != RE; ++RI) {
    BracketLocPair LocPair;
    getBracketLocPair((*RI), Dim, TheDimIdx, LocPair);

    std::stringstream TmpSS;
    SourceLocation StartLoc = (LocPair.first).getLocWithOffset(1);
    SourceLocation EndLoc = (LocPair.second).getLocWithOffset(-1);
    TmpSS << (TheDimValue + 1);
    TheRewriter.ReplaceText(SourceRange(StartLoc, EndLoc), TmpSS.str());
  }
}
