ShouldPrintBeforeOrAfterPass(const PassInfo *PI,
                                         PassOptionList &PassesToPrint) {
  for (auto *PassInf : PassesToPrint) {
    if (PassInf)
      if (PassInf->getPassArgument() == PI->getPassArgument()) {
        return true;
      }
  }
  return false;
}
