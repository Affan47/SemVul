createSparcMCCodeGenInfo(const Triple &TT,
                                               Reloc::Model RM,
                                               CodeModel::Model CM,
                                               CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();


  switch (CM) {
  default: break;
  case CodeModel::Default:
  case CodeModel::JITDefault: CM = CodeModel::Small; break;
  }

  X->initMCCodeGenInfo(RM, CM, OL);
  return X;
}
