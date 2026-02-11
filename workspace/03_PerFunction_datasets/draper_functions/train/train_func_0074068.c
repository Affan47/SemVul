addILPOpts() {
  addPass(&EarlyIfConverterID);
  if (EnableMachineCombinerPass)
    addPass(&MachineCombinerID);
  return true;
}
