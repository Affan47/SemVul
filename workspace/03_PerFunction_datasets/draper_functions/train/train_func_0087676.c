Select(SDNode *Node) {
  unsigned Opcode = Node->getOpcode();
  DebugLoc dl = Node->getDebugLoc();


  if (Node->isMachineOpcode())
    return NULL;


  switch (Opcode) {
    default: break;


    case ISD::GLOBAL_OFFSET_TABLE:
      return getGlobalBaseReg();

    case ISD::FrameIndex: {
        SDValue imm = CurDAG->getTargetConstant(0, MVT::i32);
        int FI = dyn_cast<FrameIndexSDNode>(Node)->getIndex();
        EVT VT = Node->getValueType(0);
        SDValue TFI = CurDAG->getTargetFrameIndex(FI, VT);
        unsigned Opc = MBlaze::ADDIK;
        if (Node->hasOneUse())
          return CurDAG->SelectNodeTo(Node, Opc, VT, TFI, imm);
        return CurDAG->getMachineNode(Opc, dl, VT, TFI, imm);
    }


    case MBlazeISD::JmpLink: {
      if (TM.getRelocationModel() == Reloc::PIC_) {
        SDValue Chain  = Node->getOperand(0);
        SDValue Callee = Node->getOperand(1);
        SDValue R20Reg = CurDAG->getRegister(MBlaze::R20, MVT::i32);
        SDValue InFlag(0, 0);

        if ((isa<GlobalAddressSDNode>(Callee)) ||
            (isa<ExternalSymbolSDNode>(Callee)))
        {

          SDValue GPReg = CurDAG->getRegister(MBlaze::R15, MVT::i32);


          SDValue Ops[] = { Callee, GPReg, Chain };
          SDValue Load = SDValue(CurDAG->getMachineNode(MBlaze::LW, dl,
                                 MVT::i32, MVT::Other, Ops, 3), 0);
          Chain = Load.getValue(1);


          Chain = CurDAG->getCopyToReg(Chain, dl, R20Reg, Load, InFlag);
        } else

          Chain = CurDAG->getCopyToReg(Chain, dl, R20Reg, Callee, InFlag);


        SDNode *ResNode = CurDAG->getMachineNode(MBlaze::BRLID, dl, MVT::Other,
                                                 MVT::Glue, R20Reg, Chain);
        Chain  = SDValue(ResNode, 0);
        InFlag = SDValue(ResNode, 1);
        ReplaceUses(SDValue(Node, 0), Chain);
        ReplaceUses(SDValue(Node, 1), InFlag);
        return ResNode;
      }
    }
  }


  SDNode *ResNode = SelectCode(Node);

  DEBUG(errs() << "=> ");
  if (ResNode == NULL || ResNode == Node)
    DEBUG(Node->dump(CurDAG));
  else
    DEBUG(ResNode->dump(CurDAG));
  DEBUG(errs() << "\n");
  return ResNode;
}
