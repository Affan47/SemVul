rewriteOneFieldDecl(const FieldDecl *FD)
{
  const DeclContext *Ctx = TheRecordDecl->getLexicalParent();


  if (!dyn_cast<RecordDecl>(Ctx))
    RewriteHelper->replaceUnionWithStruct(FD);
}
