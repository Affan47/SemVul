StripPointerCastsAndObjCCalls(const Value *V) {
  for (;;) {
    V = V->stripPointerCasts();
    if (!IsForwarding(GetBasicInstructionClass(V)))
      break;
    V = cast<CallInst>(V)->getArgOperand(0);
  }
  return V;
}
