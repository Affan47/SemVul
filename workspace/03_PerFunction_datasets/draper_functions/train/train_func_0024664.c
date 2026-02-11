addPreEmitPass(PassManagerBase &PM,
                                          CodeGenOpt::Level OptLevel) {
  if (Subtarget.isThumb2() && !Subtarget.prefers32BitThumb())
    PM.add(createThumb2SizeReductionPass());

  PM.add(createARMConstantIslandPass());
  return true;
}
