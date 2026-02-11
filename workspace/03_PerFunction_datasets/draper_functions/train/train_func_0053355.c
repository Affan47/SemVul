addModule(LTOModule* mod, std::string& errMsg)
{

  if(mod->getLLVVMModule()->MaterializeAllPermanently(&errMsg))
    return true;

  bool ret = _linker.LinkInModule(mod->getLLVVMModule(), &errMsg);

  const std::vector<const char*> &undefs = mod->getAsmUndefinedRefs();
  for (int i = 0, e = undefs.size(); i != e; ++i)
    _asmUndefinedRefs[undefs[i]] = 1;

  return ret;
}
