TestFuncs(const std::vector<Function*> &Funcs,
                                            std::string &Error) {


  outs() << "Checking to see if the program is misoptimized when "
         << (Funcs.size()==1 ? "this function is" : "these functions are")
         << " run through the pass"
         << (BD.getPassesToRun().size() == 1 ? "" : "es") << ":";
  PrintFunctionList(Funcs);
  outs() << '\n';


  ValueToValueMapTy VMap;
  Module *Clone = CloneModule(BD.getProgram(), VMap);
  Module *Orig = BD.swapProgramIn(Clone);

  std::vector<Function*> FuncsOnClone;
  for (unsigned i = 0, e = Funcs.size(); i != e; ++i) {
    Function *F = cast<Function>(VMap[Funcs[i]]);
    FuncsOnClone.push_back(F);
  }


  VMap.clear();
  Module *ToNotOptimize = CloneModule(BD.getProgram(), VMap);
  Module *ToOptimize = SplitFunctionsOutOfModule(ToNotOptimize, FuncsOnClone,
                                                 VMap);


  bool Broken = TestFn(BD, ToOptimize, ToNotOptimize, Error);

  delete BD.swapProgramIn(Orig);

  return Broken;
}
