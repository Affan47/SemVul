LowerAsmOperandForConstraint(SDValue Op,
                                                  std::string &Constraint,
                                                  std::vector<SDValue> &Ops,
                                                  SelectionDAG &DAG) const {

  if (Constraint.length() > 1) return;

  char ConstraintLetter = Constraint[0];
  switch (ConstraintLetter) {
  default: break;
  case 'X':
    if (Op.getOpcode() == ISD::BasicBlock) {
      Ops.push_back(Op);
      return;
    }

  case 'i':
  case 'n':
  case 's': {


    ConstantSDNode *C = dyn_cast<ConstantSDNode>(Op);
    GlobalAddressSDNode *GA = dyn_cast<GlobalAddressSDNode>(Op);


    if (Op.getOpcode() == ISD::ADD) {
      C = dyn_cast<ConstantSDNode>(Op.getOperand(1));
      GA = dyn_cast<GlobalAddressSDNode>(Op.getOperand(0));
      if (!C || !GA) {
        C = dyn_cast<ConstantSDNode>(Op.getOperand(0));
        GA = dyn_cast<GlobalAddressSDNode>(Op.getOperand(1));
      }
      if (!C || !GA)
        C = nullptr, GA = nullptr;
    }


    if (GA) {
      if (ConstraintLetter != 'n') {
        int64_t Offs = GA->getOffset();
        if (C) Offs += C->getZExtValue();
        Ops.push_back(DAG.getTargetGlobalAddress(GA->getGlobal(),
                                                 C ? SDLoc(C) : SDLoc(),
                                                 Op.getValueType(), Offs));
      }
      return;
    }
    if (C) {

      if (ConstraintLetter != 's') {


        Ops.push_back(DAG.getTargetConstant(C->getAPIntValue().getSExtValue(),
                                            SDLoc(C), MVT::i64));
      }
      return;
    }
    break;
  }
  }
}
