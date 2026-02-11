getGlobalELFType(const GlobalValue *GV) {
  if (GV->isDeclaration())
    return ELF::STT_NOTYPE;

  if (isa<Function>(GV))
    return ELF::STT_FUNC;

  return ELF::STT_OBJECT;
}
