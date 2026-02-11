emitSETCC(SelectionDAG &DAG, SDLoc DL, SDValue Glue,
                         unsigned CCValid, unsigned CCMask) {
  IPMConversion Conversion = getIPMConversion(CCValid, CCMask);
  SDValue Result = DAG.getNode(SystemZISD::IPM, DL, MVT::i32, Glue);

  if (Conversion.XORValue)
    Result = DAG.getNode(ISD::XOR, DL, MVT::i32, Result,
                         DAG.getConstant(Conversion.XORValue, DL, MVT::i32));

  if (Conversion.AddValue)
    Result = DAG.getNode(ISD::ADD, DL, MVT::i32, Result,
                         DAG.getConstant(Conversion.AddValue, DL, MVT::i32));


  Result = DAG.getNode(ISD::SRL, DL, MVT::i32, Result,
                       DAG.getConstant(Conversion.Bit, DL, MVT::i32));
  if (Conversion.Bit != 31)
    Result = DAG.getNode(ISD::AND, DL, MVT::i32, Result,
                         DAG.getConstant(1, DL, MVT::i32));
  return Result;
}
