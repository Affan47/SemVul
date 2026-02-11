fixSymbolsInTLSFixups(const MCExpr *expr) {
  switch (expr->getKind()) {
  case MCExpr::Target: llvm_unreachable("Can't handle target exprs yet!");
  case MCExpr::Constant:
    break;

  case MCExpr::Binary: {
    const MCBinaryExpr *be = cast<MCBinaryExpr>(expr);
    fixSymbolsInTLSFixups(be->getLHS());
    fixSymbolsInTLSFixups(be->getRHS());
    break;
  }

  case MCExpr::SymbolRef: {
    const MCSymbolRefExpr &symRef = *cast<MCSymbolRefExpr>(expr);
    switch (symRef.getKind()) {
    default:
      return;
    case MCSymbolRefExpr::VK_GOTTPOFF:
    case MCSymbolRefExpr::VK_INDNTPOFF:
    case MCSymbolRefExpr::VK_NTPOFF:
    case MCSymbolRefExpr::VK_GOTNTPOFF:
    case MCSymbolRefExpr::VK_TLSGD:
    case MCSymbolRefExpr::VK_TLSLD:
    case MCSymbolRefExpr::VK_TLSLDM:
    case MCSymbolRefExpr::VK_TPOFF:
    case MCSymbolRefExpr::VK_DTPOFF:
    case MCSymbolRefExpr::VK_ARM_TLSGD:
    case MCSymbolRefExpr::VK_ARM_TPOFF:
    case MCSymbolRefExpr::VK_ARM_GOTTPOFF:
      break;
    }
    MCSymbolData &SD = getAssembler().getOrCreateSymbolData(symRef.getSymbol());
    MCELF::SetType(SD, ELF::STT_TLS);
    break;
  }

  case MCExpr::Unary:
    fixSymbolsInTLSFixups(cast<MCUnaryExpr>(expr)->getSubExpr());
    break;
  }
}
