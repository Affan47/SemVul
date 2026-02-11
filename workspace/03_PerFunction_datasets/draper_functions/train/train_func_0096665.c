EmitValueImpl(const MCExpr *Value, unsigned Size, SMLoc Loc) override {
    if (const MCSymbolRefExpr *SRE = dyn_cast_or_null<MCSymbolRefExpr>(Value))
      if (SRE->getKind() == MCSymbolRefExpr::VK_ARM_SBREL && !(Size == 4))
        getContext().reportFatalError(Loc, "relocated expression must be 32-bit");

    EmitDataMappingSymbol();
    MCELFStreamer::EmitValueImpl(Value, Size);
  }
