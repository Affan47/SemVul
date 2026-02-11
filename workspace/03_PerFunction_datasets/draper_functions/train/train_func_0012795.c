evaluateAsRelocatableImpl(MCValue &Res,
                                     const MCAsmLayout *Layout,
                                     const MCFixup *Fixup) const {
  MCValue Value;

  if (!getSubExpr()->evaluateAsRelocatable(Value, Layout, Fixup))
    return false;

  if (Value.isAbsolute()) {
    int64_t Result = evaluateAsInt64(Value.getConstant());
    if ((Fixup == nullptr || (unsigned)Fixup->getKind() != PPC::fixup_ppc_half16) &&
        (Result >= 0x8000))
      return false;
    Res = MCValue::get(Result);
  } else {
    if (!Layout)
      return false;

    MCContext &Context = Layout->getAssembler().getContext();
    const MCSymbolRefExpr *Sym = Value.getSymA();
    MCSymbolRefExpr::VariantKind Modifier = Sym->getKind();
    if (Modifier != MCSymbolRefExpr::VK_None)
      return false;
    switch (Kind) {
      default:
        llvm_unreachable("Invalid kind!");
      case VK_PPC_LO:
        Modifier = MCSymbolRefExpr::VK_PPC_LO;
        break;
      case VK_PPC_HI:
        Modifier = MCSymbolRefExpr::VK_PPC_HI;
        break;
      case VK_PPC_HA:
        Modifier = MCSymbolRefExpr::VK_PPC_HA;
        break;
      case VK_PPC_HIGHERA:
        Modifier = MCSymbolRefExpr::VK_PPC_HIGHERA;
        break;
      case VK_PPC_HIGHER:
        Modifier = MCSymbolRefExpr::VK_PPC_HIGHER;
        break;
      case VK_PPC_HIGHEST:
        Modifier = MCSymbolRefExpr::VK_PPC_HIGHEST;
        break;
      case VK_PPC_HIGHESTA:
        Modifier = MCSymbolRefExpr::VK_PPC_HIGHESTA;
        break;
    }
    Sym = MCSymbolRefExpr::create(&Sym->getSymbol(), Modifier, Context);
    Res = MCValue::get(Sym, Value.getSymB(), Value.getConstant());
  }

  return true;
}
