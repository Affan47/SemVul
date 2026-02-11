AnalyzeCallResult(EVT VT, CCAssignFn Fn) {
  if (Fn(0, VT, VT, CCValAssign::Full, ISD::ArgFlagsTy(), *this)) {
#ifndef NDEBUG
    dbgs() << "Call result has unhandled type "
           << VT.getEVTString();
#endif
    llvm_unreachable(0);
  }
}
