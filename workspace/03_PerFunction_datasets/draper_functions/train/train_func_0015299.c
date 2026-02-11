LowerCall(SDValue Chain, SDValue Callee,
                             CallingConv::ID CallConv, bool isVarArg,
                             bool &isTailCall,
                             const SmallVectorImpl<ISD::OutputArg> &Outs,
                             const SmallVectorImpl<SDValue> &OutVals,
                             const SmallVectorImpl<ISD::InputArg> &Ins,
                             DebugLoc dl, SelectionDAG &DAG,
                             SmallVectorImpl<SDValue> &InVals) const {
  if (isTailCall)
    isTailCall = IsEligibleForTailCallOptimization(Callee, CallConv, isVarArg,
                                                   Ins, DAG);

  if (PPCSubTarget.isSVR4ABI() && !PPCSubTarget.isPPC64())
    return LowerCall_SVR4(Chain, Callee, CallConv, isVarArg,
                          isTailCall, Outs, OutVals, Ins,
                          dl, DAG, InVals);

  return LowerCall_Darwin(Chain, Callee, CallConv, isVarArg,
                          isTailCall, Outs, OutVals, Ins,
                          dl, DAG, InVals);
}
