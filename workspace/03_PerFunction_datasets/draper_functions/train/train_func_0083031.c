analyzeFunction(Function *F,
                                                       const TargetData *TD) {
  Metrics.analyzeFunction(F, TD);


  if (Metrics.NumRets==1)
    --Metrics.NumInsts;


  ArgumentWeights.reserve(F->arg_size());
  for (Function::arg_iterator I = F->arg_begin(), E = F->arg_end(); I != E; ++I)
    ArgumentWeights.push_back(ArgInfo(Metrics.CountCodeReductionForConstant(I),
                                      Metrics.CountCodeReductionForAlloca(I)));
}
