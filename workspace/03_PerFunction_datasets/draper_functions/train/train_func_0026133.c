createMBlazeMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                                CodeModel::Model CM) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  if (RM == Reloc::Default)
    RM = Reloc::Static;
  if (CM == CodeModel::Default)
    CM = CodeModel::Small;
  X->InitMCCodeGenInfo(RM, CM);
  return X;
}
