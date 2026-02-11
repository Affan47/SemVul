insertStringBeforeFunc(const FunctionDecl *FD,
                                          const std::string &Str)
{
  SourceRange FuncRange;
  if (FunctionTemplateDecl *TmplD = FD->getDescribedFunctionTemplate()) {
    FuncRange = TmplD->getSourceRange();
  }
  else {
    FuncRange = FD->getSourceRange();
  }
  SourceLocation StartLoc = FuncRange.getBegin();
  return !TheRewriter->InsertTextBefore(StartLoc, Str);
}
