createMipsMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                              CodeModel::Model CM) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  if (RM == Reloc::Default)
    RM = Reloc::PIC_;
  X->InitMCCodeGenInfo(RM, CM);
  return X;
}
