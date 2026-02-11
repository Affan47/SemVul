PrepareTailCall(SelectionDAG &DAG, SDValue &InFlag, SDValue &Chain,
                     DebugLoc dl, bool isPPC64, int SPDiff, unsigned NumBytes,
                     SDValue LROp, SDValue FPOp, bool isDarwinABI,
                     SmallVector<TailCallArgumentInfo, 8> &TailCallArguments) {
  MachineFunction &MF = DAG.getMachineFunction();


  SmallVector<SDValue, 8> MemOpChains2;

  InFlag = SDValue();
  StoreTailCallArgumentsToStackSlot(DAG, Chain, TailCallArguments,
                                    MemOpChains2, dl);
  if (!MemOpChains2.empty())
    Chain = DAG.getNode(ISD::TokenFactor, dl, MVT::Other,
                        &MemOpChains2[0], MemOpChains2.size());


  Chain = EmitTailCallStoreFPAndRetAddr(DAG, MF, Chain, LROp, FPOp, SPDiff,
                                        isPPC64, isDarwinABI, dl);


  Chain = DAG.getCALLSEQ_END(Chain, DAG.getIntPtrConstant(NumBytes, true),
                             DAG.getIntPtrConstant(0, true), InFlag);
  InFlag = Chain.getValue(1);
}
