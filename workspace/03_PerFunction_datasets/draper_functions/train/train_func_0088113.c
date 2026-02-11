SelectInlineAsmMemoryOperand(const SDValue &Op, char ConstraintCode,
                             std::vector<SDValue> &OutOps) {
  SDValue Op0, Op1, Op2, Op3, Op4;
  switch (ConstraintCode) {
  case 'o':
  case 'v':
  default: return true;
  case 'm':
    if (!SelectAddr(Op.getNode(), Op, Op0, Op1, Op2, Op3, Op4))
      return true;
    break;
  }

  OutOps.push_back(Op0);
  OutOps.push_back(Op1);
  OutOps.push_back(Op2);
  OutOps.push_back(Op3);
  OutOps.push_back(Op4);
  return false;
}
