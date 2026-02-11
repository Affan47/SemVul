makeAddress(SDValue Op, SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = getPointerTy(DAG.getDataLayout());


  if (getTargetMachine().getRelocationModel() == Reloc::PIC_) {

    SDValue HiLo = makeHiLoPair(Op, SparcMCExpr::VK_Sparc_GOT22,
                                SparcMCExpr::VK_Sparc_GOT10, DAG);
    SDValue GlobalBase = DAG.getNode(SPISD::GLOBAL_BASE_REG, DL, VT);
    SDValue AbsAddr = DAG.getNode(ISD::ADD, DL, VT, GlobalBase, HiLo);


    MachineFrameInfo *MFI = DAG.getMachineFunction().getFrameInfo();
    MFI->setHasCalls(true);
    return DAG.getLoad(VT, DL, DAG.getEntryNode(), AbsAddr,
                       MachinePointerInfo::getGOT(DAG.getMachineFunction()),
                       false, false, false, 0);
  }


  switch(getTargetMachine().getCodeModel()) {
  default:
    llvm_unreachable("Unsupported absolute code model");
  case CodeModel::Small:

    return makeHiLoPair(Op, SparcMCExpr::VK_Sparc_HI,
                        SparcMCExpr::VK_Sparc_LO, DAG);
  case CodeModel::Medium: {

    SDValue H44 = makeHiLoPair(Op, SparcMCExpr::VK_Sparc_H44,
                               SparcMCExpr::VK_Sparc_M44, DAG);
    H44 = DAG.getNode(ISD::SHL, DL, VT, H44, DAG.getConstant(12, DL, MVT::i32));
    SDValue L44 = withTargetFlags(Op, SparcMCExpr::VK_Sparc_L44, DAG);
    L44 = DAG.getNode(SPISD::Lo, DL, VT, L44);
    return DAG.getNode(ISD::ADD, DL, VT, H44, L44);
  }
  case CodeModel::Large: {

    SDValue Hi = makeHiLoPair(Op, SparcMCExpr::VK_Sparc_HH,
                              SparcMCExpr::VK_Sparc_HM, DAG);
    Hi = DAG.getNode(ISD::SHL, DL, VT, Hi, DAG.getConstant(32, DL, MVT::i32));
    SDValue Lo = makeHiLoPair(Op, SparcMCExpr::VK_Sparc_HI,
                              SparcMCExpr::VK_Sparc_LO, DAG);
    return DAG.getNode(ISD::ADD, DL, VT, Hi, Lo);
  }
  }
}
