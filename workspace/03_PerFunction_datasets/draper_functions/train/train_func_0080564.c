AnalyzeCallOperands(SmallVectorImpl<MVT> &ArgVTs,
                                  SmallVectorImpl<ISD::ArgFlagsTy> &Flags,
                                  CCAssignFn Fn) {
  unsigned NumOps = ArgVTs.size();
  for (unsigned i = 0; i != NumOps; ++i) {
    MVT ArgVT = ArgVTs[i];
    ISD::ArgFlagsTy ArgFlags = Flags[i];
    if (Fn(i, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, *this)) {
#ifndef NDEBUG
      dbgs() << "Call operand #" << i << " has unhandled type "
             << EVT(ArgVT).getEVTString() << '\n';
#endif
      llvm_unreachable(nullptr);
    }
  }
}
