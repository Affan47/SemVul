imBinFileSetCurrentModule(int pModule)
{
  int old_module = iBinFileModuleCurrent;

  if (pModule >= iBinFileModuleCount)
    return -1;

  iBinFileModuleCurrent = pModule;

  return old_module;
}
