TestOptimizer(BugDriver &BD, Module *Test, Module *Safe,
                          std::string &Error) {


  outs() << "  Optimizing functions being tested: ";
  Module *Optimized = BD.runPassesOn(Test, BD.getPassesToRun(),
                                     true);
  outs() << "done.\n";
  delete Test;

  outs() << "  Checking to see if the merged program executes correctly: ";
  bool Broken;
  Module *New = TestMergedProgram(BD, Optimized, Safe, true, Error, Broken);
  if (New) {
    outs() << (Broken ? " nope.\n" : " yup.\n");

    delete BD.swapProgramIn(New);
  }
  return Broken;
}
