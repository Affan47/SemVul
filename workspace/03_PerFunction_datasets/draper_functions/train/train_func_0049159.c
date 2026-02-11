LowerFormalArguments(SDValue Chain,
                                        CallingConv::ID CallConv, bool isVarArg,
                                        const SmallVectorImpl<ISD::InputArg>
                                          &Ins,
                                        DebugLoc dl, SelectionDAG &DAG,
                                        SmallVectorImpl<SDValue> &InVals)
                                          const {
  if (PPCSubTarget.isSVR4ABI() && !PPCSubTarget.isPPC64()) {
    return LowerFormalArguments_SVR4(Chain, CallConv, isVarArg, Ins,
                                     dl, DAG, InVals);
  } else {
    return LowerFormalArguments_Darwin(Chain, CallConv, isVarArg, Ins,
                                       dl, DAG, InVals);
  }
}
