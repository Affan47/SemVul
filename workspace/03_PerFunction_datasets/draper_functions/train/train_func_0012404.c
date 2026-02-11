getEncodedThreadLocalMode(const GlobalValue &GV) {
  switch (GV.getThreadLocalMode()) {
    case GlobalVariable::NotThreadLocal:         return 0;
    case GlobalVariable::GeneralDynamicTLSModel: return 1;
    case GlobalVariable::LocalDynamicTLSModel:   return 2;
    case GlobalVariable::InitialExecTLSModel:    return 3;
    case GlobalVariable::LocalExecTLSModel:      return 4;
  }
  llvm_unreachable("Invalid TLS model");
}
