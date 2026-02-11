printGlobal(const GlobalVariable *GV) {
  if (GV->isMaterializable())
    Out << "; Materializable\n";

  WriteAsOperandInternal(Out, GV, &TypePrinter, &Machine, GV->getParent());
  Out << " = ";

  if (!GV->hasInitializer() && GV->hasExternalLinkage())
    Out << "external ";

  PrintLinkage(GV->getLinkage(), Out);
  PrintVisibility(GV->getVisibility(), Out);
  PrintDLLStorageClass(GV->getDLLStorageClass(), Out);
  PrintThreadLocalModel(GV->getThreadLocalMode(), Out);
  if (GV->hasUnnamedAddr())
    Out << "unnamed_addr ";

  if (unsigned AddressSpace = GV->getType()->getAddressSpace())
    Out << "addrspace(" << AddressSpace << ") ";
  if (GV->isExternallyInitialized()) Out << "externally_initialized ";
  Out << (GV->isConstant() ? "constant " : "global ");
  TypePrinter.print(GV->getType()->getElementType(), Out);

  if (GV->hasInitializer()) {
    Out << ' ';
    writeOperand(GV->getInitializer(), false);
  }

  if (GV->hasSection()) {
    Out << ", section \"";
    PrintEscapedString(GV->getSection(), Out);
    Out << '"';
  }
  maybePrintComdat(Out, *GV);
  if (GV->getAlignment())
    Out << ", align " << GV->getAlignment();

  printInfoComment(*GV);
}
