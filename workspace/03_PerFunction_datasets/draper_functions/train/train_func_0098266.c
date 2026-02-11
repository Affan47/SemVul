EmitSwapFPIntRetval(
    const MCSubtargetInfo &STI, Mips16HardFloatInfo::FPReturnVariant RV,
    bool LE) {
  using namespace Mips16HardFloatInfo;
  unsigned MovOpc = Mips::MFC1;
  switch (RV) {
  case FRet:
    EmitInstrRegReg(STI, MovOpc, Mips::V0, Mips::F0);
    break;
  case DRet:
    EmitMovFPIntPair(STI, MovOpc, Mips::V0, Mips::V1, Mips::F0, Mips::F1, LE);
    break;
  case CFRet:
    EmitMovFPIntPair(STI, MovOpc, Mips::V0, Mips::V1, Mips::F0, Mips::F1, LE);
    break;
  case CDRet:
    EmitMovFPIntPair(STI, MovOpc, Mips::V0, Mips::V1, Mips::F0, Mips::F1, LE);
    EmitMovFPIntPair(STI, MovOpc, Mips::A0, Mips::A1, Mips::F2, Mips::F3, LE);
    break;
  case NoFPRet:
    break;
  }
}
