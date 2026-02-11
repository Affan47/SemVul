printVariableBody(const GlobalVariable *GV) {
  if (GV->hasInitializer()) {
    printCppName(GV);
    Out << "->setInitializer(";
    Out << getCppName(GV->getInitializer()) << ");";
    nl(Out);
  }
}
