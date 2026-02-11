verifyPreservedAnalysis(Pass *P) {

#ifdef NDEBUG
  return;
#endif
  AnalysisUsage *AnUsage = TPM->findAnalysisUsage(P);
  const AnalysisUsage::VectorType &PreservedSet = AnUsage->getPreservedSet();


  for (AnalysisUsage::VectorType::const_iterator I = PreservedSet.begin(),
         E = PreservedSet.end(); I != E; ++I) {
    AnalysisID AID = *I;
    if (Pass *AP = findAnalysisPass(AID, true)) {
      TimeRegion PassTimer(getPassTimer(AP));
      AP->verifyAnalysis();
    }
  }
}
