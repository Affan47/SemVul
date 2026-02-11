LowerConstantPool(SDValue Op,
                                               SelectionDAG &DAG) const {
  ConstantPoolSDNode *N = cast<ConstantPoolSDNode>(Op);

  DebugLoc dl = Op.getDebugLoc();
  const Constant *C = N->getConstVal();
  SDValue CP = DAG.getTargetConstantPool(C, MVT::i32, N->getAlignment());
  SDValue Hi = DAG.getNode(SPISD::Hi, dl, MVT::i32, CP);
  SDValue Lo = DAG.getNode(SPISD::Lo, dl, MVT::i32, CP);
  if (getTargetMachine().getRelocationModel() != Reloc::PIC_)
    return DAG.getNode(ISD::ADD, dl, MVT::i32, Lo, Hi);

  SDValue GlobalBase = DAG.getNode(SPISD::GLOBAL_BASE_REG, dl,
                                   getPointerTy());
  SDValue RelAddr = DAG.getNode(ISD::ADD, dl, MVT::i32, Lo, Hi);
  SDValue AbsAddr = DAG.getNode(ISD::ADD, dl, MVT::i32,
                                GlobalBase, RelAddr);
  return DAG.getLoad(getPointerTy(), dl, DAG.getEntryNode(),
                     AbsAddr, MachinePointerInfo(), false, false, 0);
}
