PromoteSetCCOperands(SDValue &NewLHS,SDValue &NewRHS,
                                            ISD::CondCode CCCode) {


  switch (CCCode) {
  default: llvm_unreachable("Unknown integer comparison!");
  case ISD::SETEQ:
  case ISD::SETNE: {
    SDValue OpL = GetPromotedInteger(NewLHS);
    SDValue OpR = GetPromotedInteger(NewRHS);


    if (OpL->getOpcode() == ISD::AssertSext &&
        cast<VTSDNode>(OpL->getOperand(1))->getVT() == NewLHS.getValueType() &&
        OpR->getOpcode() == ISD::AssertSext &&
        cast<VTSDNode>(OpR->getOperand(1))->getVT() == NewRHS.getValueType()) {
      NewLHS = OpL;
      NewRHS = OpR;
    } else {
      NewLHS = ZExtPromotedInteger(NewLHS);
      NewRHS = ZExtPromotedInteger(NewRHS);
    }
    break;
  }
  case ISD::SETUGE:
  case ISD::SETUGT:
  case ISD::SETULE:
  case ISD::SETULT:


    NewLHS = ZExtPromotedInteger(NewLHS);
    NewRHS = ZExtPromotedInteger(NewRHS);
    break;
  case ISD::SETGE:
  case ISD::SETGT:
  case ISD::SETLT:
  case ISD::SETLE:
    NewLHS = SExtPromotedInteger(NewLHS);
    NewRHS = SExtPromotedInteger(NewRHS);
    break;
  }
}
