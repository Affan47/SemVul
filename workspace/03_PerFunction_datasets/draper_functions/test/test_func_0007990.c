findFuncSignature(const char *name) {
  const char *name_;
  int i = 0;
  while (PredefinedFuncs[i].Name) {
    name_ = PredefinedFuncs[i].Name;
    if (strcmp(name, name_) == 0)
      return &PredefinedFuncs[i].Signature;
    i++;
  }
  return nullptr;
}
