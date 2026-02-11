getInitStrWithNonPointerType(const Expr *Exp,
                                                 std::string &Str)
{
  std::string ExprStr("");
  RewriteHelper->getExprString(Exp, ExprStr);

  RecordDecl::field_iterator I = TheRecordDecl->field_begin();
  RecordDecl::field_iterator E = TheRecordDecl->field_end();
  TransAssert((I != E) && "Empty RecordDecl!");
  Str = ExprStr;
  ++I;

  if (I == E)
    return;

  for (; I != E; ++I) {
    Str += ",";
    const FieldDecl *FD = (*I);
    const Type *FTy = FD->getType().getTypePtr();
    if (FTy->isPointerType())
      Str += "0";
    else
      Str += ExprStr;
  }
}
