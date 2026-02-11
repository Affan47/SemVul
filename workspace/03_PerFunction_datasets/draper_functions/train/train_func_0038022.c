calculateSEHStateNumbers(const Function *Fn,
                                    WinEHFuncInfo &FuncInfo) {

  if (!FuncInfo.SEHUnwindMap.empty())
    return;

  for (const BasicBlock &BB : *Fn) {
    if (!BB.isEHPad() || !doesEHPadUnwindToCaller(BB.getFirstNonPHI()))
      continue;
    calculateExplicitSEHStateNumbers(FuncInfo, BB, -1);
  }
}
