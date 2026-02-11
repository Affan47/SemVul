LowerCall(CallLoweringInfo &CLI,
                                        SmallVectorImpl<SDValue> &InVals) const {
  SDValue Callee = CLI.Callee;
  SelectionDAG &DAG = CLI.DAG;

  const Function &Fn = *DAG.getMachineFunction().getFunction();

  StringRef FuncName("<unknown>");

  if (const ExternalSymbolSDNode *G = dyn_cast<ExternalSymbolSDNode>(Callee))
    FuncName = G->getSymbol();
  else if (const GlobalAddressSDNode *G = dyn_cast<GlobalAddressSDNode>(Callee))
    FuncName = G->getGlobal()->getName();

  DiagnosticInfoUnsupported NoCalls(Fn, "call to function " + FuncName);
  DAG.getContext()->diagnose(NoCalls);
  return SDValue();
}
