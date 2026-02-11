getShiftOp(unsigned Imm) const {
  switch (ARM_AM::getAM2ShiftOpc(Imm)) {
  default: llvm_unreachable("Unknown shift opc!");
  case ARM_AM::asr: return 2;
  case ARM_AM::lsl: return 0;
  case ARM_AM::lsr: return 1;
  case ARM_AM::ror:
  case ARM_AM::rrx: return 3;
  }
  return 0;
}
