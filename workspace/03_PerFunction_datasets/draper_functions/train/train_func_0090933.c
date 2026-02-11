EmitFunctionEntryCode() {

  if (const Function *Fn = MF->getFunction())
    if (Fn->hasExternalLinkage() && Fn->getName() == "main")
      emitSpecialCodeForMain();
}
