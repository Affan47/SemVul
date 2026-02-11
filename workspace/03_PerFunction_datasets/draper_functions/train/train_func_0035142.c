getGlobalVariableClass(const GlobalVariable *GV) {

  if (GV->hasAppendingLinkage() && GV->use_empty()) {
    if (GV->getName() == "llvm.global_ctors")
      return GlobalCtors;
    else if (GV->getName() == "llvm.global_dtors")
      return GlobalDtors;
  }


  if (GV->getSection() == "llvm.metadata")
    return NotPrinted;

  return NotSpecial;
}
