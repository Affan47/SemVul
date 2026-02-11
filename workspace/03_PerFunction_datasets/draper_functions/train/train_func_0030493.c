SelectGlobalValueVariableOffset(SDValue Addr,
    SDValue& BaseReg, SDValue &Offset) {
  if (!isa<ConstantSDNode>(Addr)) {
    BaseReg = Addr;
    Offset = CurDAG->getIntPtrConstant(0, SDLoc(Addr), true);
    return true;
  }
  return false;
}
