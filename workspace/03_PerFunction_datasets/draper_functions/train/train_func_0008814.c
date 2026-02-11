codeand (CompileState *compst, TTree *tree, int tt) {
  int n = fixedlen(tree);
  if (n >= 0 && n <= MAXBEHIND && !hascaptures(tree)) {
    codegen(compst, tree, 0, tt, fullset);
    if (n > 0)
      addinstruction(compst, IBehind, n);
  }
  else {
    int pcommit;
    int pchoice = addoffsetinst(compst, IChoice);
    codegen(compst, tree, 0, tt, fullset);
    pcommit = addoffsetinst(compst, IBackCommit);
    jumptohere(compst, pchoice);
    addinstruction(compst, IFail, 0);
    jumptohere(compst, pcommit);
  }
}
