HandleTranslationUnit(ASTContext &Ctx)
{
  CollectionVisitor->TraverseDecl(Ctx.getTranslationUnitDecl());

  if (QueryInstanceOnly)
    return;

  if (TransformationCounter > ValidInstanceNum) {
    TransError = TransMaxInstanceError;
    return;
  }
  if (ToCounter > ValidInstanceNum) {
    TransError = TransToCounterTooBigError;
    return;
  }

  Ctx.getDiagnostics().setSuppressAllDiagnostics(false);

  doRewriting();

  if (Ctx.getDiagnostics().hasErrorOccurred() ||
      Ctx.getDiagnostics().hasFatalErrorOccurred())
    TransError = TransInternalError;
}
