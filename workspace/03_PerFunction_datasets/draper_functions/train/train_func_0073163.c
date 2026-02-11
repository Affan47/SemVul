createJIT(Module *M,
                                  std::string *ErrorStr,
                                  JITMemoryManager *JMM,
                                  CodeGenOpt::Level OptLevel,
                                  bool GVsWithCode,
                                  TargetMachine *TM) {


  sys::DynamicLibrary::LoadLibraryPermanently(0, NULL);


  if (TargetJITInfo *TJ = TM->getJITInfo())
    return new MCJIT(M, TM, *TJ, new MCJITMemoryManager(JMM, M), OptLevel,
                     GVsWithCode);

  if (ErrorStr)
    *ErrorStr = "target does not support JIT code generation";
  return 0;
}
