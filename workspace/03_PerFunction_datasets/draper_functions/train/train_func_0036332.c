printTLSCall(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O) {


  const MCOperand &Op = MI->getOperand(OpNo);
  const MCSymbolRefExpr &refExp = cast<MCSymbolRefExpr>(*Op.getExpr());
  O << refExp.getSymbol().getName();
  O << '(';
  printOperand(MI, OpNo+1, O);
  O << ')';
  if (refExp.getKind() != MCSymbolRefExpr::VK_None)
    O << '@' << MCSymbolRefExpr::getVariantKindName(refExp.getKind());
}
