getVectorCmp(SelectionDAG &DAG, unsigned Opcode, SDLoc DL,
                            EVT VT, SDValue CmpOp0, SDValue CmpOp1) {


  if (CmpOp0.getValueType() == MVT::v4f32) {
    SDValue H0 = expandV4F32ToV2F64(DAG, 0, DL, CmpOp0);
    SDValue L0 = expandV4F32ToV2F64(DAG, 2, DL, CmpOp0);
    SDValue H1 = expandV4F32ToV2F64(DAG, 0, DL, CmpOp1);
    SDValue L1 = expandV4F32ToV2F64(DAG, 2, DL, CmpOp1);
    SDValue HRes = DAG.getNode(Opcode, DL, MVT::v2i64, H0, H1);
    SDValue LRes = DAG.getNode(Opcode, DL, MVT::v2i64, L0, L1);
    return DAG.getNode(SystemZISD::PACK, DL, VT, HRes, LRes);
  }
  return DAG.getNode(Opcode, DL, VT, CmpOp0, CmpOp1);
}
