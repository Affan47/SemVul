EmitFunctionEntryLabel() {
  CurrentFnSym->redefineIfPossible();


  if (CurrentFnSym->isVariable())
    report_fatal_error("'" + Twine(CurrentFnSym->getName()) +
                       "' is a protected alias");
  if (CurrentFnSym->isDefined())
    report_fatal_error("'" + Twine(CurrentFnSym->getName()) +
                       "' label emitted multiple times to assembly file");

  return OutStreamer->EmitLabel(CurrentFnSym);
}
