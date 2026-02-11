EmitAdjustRSP(MCContext &Ctx, MCStreamer &Out, long Offset) {
    const MCExpr *Disp = MCConstantExpr::create(Offset, Ctx);
    std::unique_ptr<X86Operand> Op(
        X86Operand::CreateMem(getPointerWidth(), 0, Disp, X86::RSP, 0, 1,
                              SMLoc(), SMLoc()));
    EmitLEA(*Op, MVT::i64, X86::RSP, Out);
    OrigSPOffset += Offset;
  }
