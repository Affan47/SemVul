printAlias(const GlobalAlias *GA) {
  if (GA->isMaterializable())
    Out << "; Materializable\n";


  if (!GA->hasName())
    Out << "<<nameless>> = ";
  else {
    PrintLLVMName(Out, GA);
    Out << " = ";
  }
  PrintVisibility(GA->getVisibility(), Out);

  Out << "alias ";

  PrintLinkage(GA->getLinkage(), Out);

  const Constant *Aliasee = GA->getAliasee();

  if (Aliasee == 0) {
    TypePrinter.print(GA->getType(), Out);
    Out << " <<NULL ALIASEE>>";
  } else {
    writeOperand(Aliasee, !isa<ConstantExpr>(Aliasee));
  }

  printInfoComment(*GA);
  Out << '\n';
}
