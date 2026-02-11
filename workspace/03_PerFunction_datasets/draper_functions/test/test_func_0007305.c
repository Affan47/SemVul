addPreRegAlloc(PassManagerBase &PM, CodeGenOpt::Level OptLevel) {


  if (!Subtarget.hasMips64())
    PM.add(createMipsEmitGPRestorePass(*this));
  return true;
}
