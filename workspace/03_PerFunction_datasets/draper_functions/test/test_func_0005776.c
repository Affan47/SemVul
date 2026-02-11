LowerConstantPool(SDValue Op, SelectionDAG &DAG) const
{
  ConstantPoolSDNode *CP = cast<ConstantPoolSDNode>(Op);

  DebugLoc dl = CP->getDebugLoc();
  EVT PtrVT = Op.getValueType();
  SDValue Res;
  if (CP->isMachineConstantPoolEntry()) {
    Res = DAG.getTargetConstantPool(CP->getMachineCPVal(), PtrVT,
                                    CP->getAlignment());
  } else {
    Res = DAG.getTargetConstantPool(CP->getConstVal(), PtrVT,
                                    CP->getAlignment());
  }
  return DAG.getNode(XCoreISD::CPRelativeWrapper, dl, MVT::i32, Res);
}
