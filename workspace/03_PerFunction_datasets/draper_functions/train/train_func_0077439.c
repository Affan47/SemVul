IsEligibleForTailCallOptimization(
                                 SDValue Callee,
                                 CallingConv::ID CalleeCC,
                                 bool isVarArg,
                                 bool isCalleeStructRet,
                                 bool isCallerStructRet,
                                 const SmallVectorImpl<ISD::OutputArg> &Outs,
                                 const SmallVectorImpl<SDValue> &OutVals,
                                 const SmallVectorImpl<ISD::InputArg> &Ins,
                                 SelectionDAG& DAG) const {
  const Function *CallerF = DAG.getMachineFunction().getFunction();
  CallingConv::ID CallerCC = CallerF->getCallingConv();
  bool CCMatch = CallerCC == CalleeCC;


  if (!(dyn_cast<GlobalAddressSDNode>(Callee))
      && !(dyn_cast<ExternalSymbolSDNode>(Callee))) {
    return false;
  }


  if (!CCMatch)
    return false;


  if (isVarArg)
    return false;


  if (isCalleeStructRet || isCallerStructRet)
    return false;


  return true;
}
