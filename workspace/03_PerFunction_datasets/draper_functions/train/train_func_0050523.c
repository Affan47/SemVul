SelectInlineAsmMemoryOperand(const SDValue &Op, unsigned ConstraintID,
                             std::vector<SDValue> &OutOps) {
  SDValue Reg;
  switch (ConstraintID) {
  default: return true;
  case InlineAsm::Constraint_m:
    switch (Op.getOpcode()) {
    default: return true;
    case XCoreISD::CPRelativeWrapper:
      Reg = CurDAG->getRegister(XCore::CP, MVT::i32);
      break;
    case XCoreISD::DPRelativeWrapper:
      Reg = CurDAG->getRegister(XCore::DP, MVT::i32);
      break;
    }
  }
  OutOps.push_back(Reg);
  OutOps.push_back(Op.getOperand(0));
  return false;
}
