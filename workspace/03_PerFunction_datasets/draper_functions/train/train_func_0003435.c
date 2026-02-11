printMCExpr(const MCExpr &Expr, raw_ostream &OS) {
  switch (Expr.getKind()) {
  case MCExpr::Target:
    return cast<MCTargetExpr>(&Expr)->printImpl(OS, MAI);
  case MCExpr::Constant:
    OS << cast<MCConstantExpr>(Expr).getValue();
    return;

  case MCExpr::SymbolRef: {
    const MCSymbolRefExpr &SRE = cast<MCSymbolRefExpr>(Expr);
    const MCSymbol &Sym = SRE.getSymbol();
    Sym.print(OS, MAI);
    return;
  }

  case MCExpr::Unary: {
    const MCUnaryExpr &UE = cast<MCUnaryExpr>(Expr);
    switch (UE.getOpcode()) {
    case MCUnaryExpr::LNot:  OS << '!'; break;
    case MCUnaryExpr::Minus: OS << '-'; break;
    case MCUnaryExpr::Not:   OS << '~'; break;
    case MCUnaryExpr::Plus:  OS << '+'; break;
    }
    printMCExpr(*UE.getSubExpr(), OS);
    return;
  }

  case MCExpr::Binary: {
    const MCBinaryExpr &BE = cast<MCBinaryExpr>(Expr);


    if (isa<MCConstantExpr>(BE.getLHS()) || isa<MCSymbolRefExpr>(BE.getLHS()) ||
        isa<NVPTXGenericMCSymbolRefExpr>(BE.getLHS())) {
      printMCExpr(*BE.getLHS(), OS);
    } else {
      OS << '(';
      printMCExpr(*BE.getLHS(), OS);
      OS<< ')';
    }

    switch (BE.getOpcode()) {
    case MCBinaryExpr::Add:

      if (const MCConstantExpr *RHSC = dyn_cast<MCConstantExpr>(BE.getRHS())) {
        if (RHSC->getValue() < 0) {
          OS << RHSC->getValue();
          return;
        }
      }

      OS <<  '+';
      break;
    default: llvm_unreachable("Unhandled binary operator");
    }


    if (isa<MCConstantExpr>(BE.getRHS()) || isa<MCSymbolRefExpr>(BE.getRHS())) {
      printMCExpr(*BE.getRHS(), OS);
    } else {
      OS << '(';
      printMCExpr(*BE.getRHS(), OS);
      OS << ')';
    }
    return;
  }
  }

  llvm_unreachable("Invalid expression kind!");
}
