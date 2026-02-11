fixELFSymbolsInTLSFixupsImpl(const MCExpr *Expr, MCAssembler &Asm) {
  switch (Expr->getKind()) {
  case MCExpr::Target:
    llvm_unreachable("Can't handle nested target expression");
    break;
  case MCExpr::Constant:
    break;

  case MCExpr::Binary: {
    const MCBinaryExpr *BE = cast<MCBinaryExpr>(Expr);
    fixELFSymbolsInTLSFixupsImpl(BE->getLHS(), Asm);
    fixELFSymbolsInTLSFixupsImpl(BE->getRHS(), Asm);
    break;
  }

  case MCExpr::SymbolRef: {


    const MCSymbolRefExpr &SymRef = *cast<MCSymbolRefExpr>(Expr);
    cast<MCSymbolELF>(SymRef.getSymbol()).setType(ELF::STT_TLS);
    break;
  }

  case MCExpr::Unary:
    fixELFSymbolsInTLSFixupsImpl(cast<MCUnaryExpr>(Expr)->getSubExpr(), Asm);
    break;
  }
}
