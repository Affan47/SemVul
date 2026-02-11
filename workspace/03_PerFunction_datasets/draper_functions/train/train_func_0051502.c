ShouldPrintBeforeOrAfterPass(const void *PassID,
                                         PassOptionList &PassesToPrint) {
  if (const llvm::PassInfo *PI =
      PassRegistry::getPassRegistry()->getPassInfo(PassID)) {
    for (unsigned i = 0, ie = PassesToPrint.size(); i < ie; ++i) {
      const llvm::PassInfo *PassInf = PassesToPrint[i];
      if (PassInf)
        if (PassInf->getPassArgument() == PI->getPassArgument()) {
          return true;
        }
    }
  }
  return false;
}
