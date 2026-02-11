Select(SDNode *N) {
  DebugLoc dl = N->getDebugLoc();
  if (N->isMachineOpcode())
    return NULL;

  switch (N->getOpcode()) {
  default: break;
  case SPISD::GLOBAL_BASE_REG:
    return getGlobalBaseReg();

  case ISD::SDIV:
  case ISD::UDIV: {

    SDValue DivLHS = N->getOperand(0);
    SDValue DivRHS = N->getOperand(1);


    SDValue TopPart;
    if (N->getOpcode() == ISD::SDIV) {
      TopPart = SDValue(CurDAG->getMachineNode(SP::SRAri, dl, MVT::i32, DivLHS,
                                   CurDAG->getTargetConstant(31, MVT::i32)), 0);
    } else {
      TopPart = CurDAG->getRegister(SP::G0, MVT::i32);
    }
    TopPart = SDValue(CurDAG->getMachineNode(SP::WRYrr, dl, MVT::Glue, TopPart,
                                     CurDAG->getRegister(SP::G0, MVT::i32)), 0);


    unsigned Opcode = N->getOpcode() == ISD::SDIV ? SP::SDIVrr : SP::UDIVrr;
    return CurDAG->SelectNodeTo(N, Opcode, MVT::i32, DivLHS, DivRHS,
                                TopPart);
  }
  case ISD::MULHU:
  case ISD::MULHS: {

    SDValue MulLHS = N->getOperand(0);
    SDValue MulRHS = N->getOperand(1);
    unsigned Opcode = N->getOpcode() == ISD::MULHU ? SP::UMULrr : SP::SMULrr;
    SDNode *Mul = CurDAG->getMachineNode(Opcode, dl, MVT::i32, MVT::Glue,
                                         MulLHS, MulRHS);

    return CurDAG->SelectNodeTo(N, SP::RDY, MVT::i32, SDValue(Mul, 1));
    return NULL;
  }
  }

  return SelectCode(N);
}
