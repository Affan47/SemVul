addInstSelector() {

  addPass(createPPCISelDag(getPPCTargetMachine()));

#ifndef NDEBUG
  if (!DisableCTRLoops && getOptLevel() != CodeGenOpt::None)
    addPass(createPPCCTRLoopsVerify());
#endif

  addPass(createPPCVSXCopyPass());
  return false;
}
