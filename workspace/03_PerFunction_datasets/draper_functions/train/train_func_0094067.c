LowerConstantPool(SDValue Op, SelectionDAG &DAG) const
{
  ConstantPoolSDNode *CP = cast<ConstantPoolSDNode>(Op);

  SDLoc dl(CP);
  EVT PtrVT = Op.getValueType();
  SDValue Res;
  if (CP->isMachineConstantPoolEntry()) {
    Res = DAG.getTargetConstantPool(CP->getMachineCPVal(), PtrVT,
                                    CP->getAlignment(), CP->getOffset());
  } else {
    Res = DAG.getTargetConstantPool(CP->getConstVal(), PtrVT,
                                    CP->getAlignment(), CP->getOffset());
  }
  return DAG.getNode(XCoreISD::CPRelativeWrapper, dl, MVT::i32, Res);
}
