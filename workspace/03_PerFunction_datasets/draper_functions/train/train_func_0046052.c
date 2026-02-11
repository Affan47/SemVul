createARMMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                             CodeModel::Model CM) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  if (RM == Reloc::Default) {
    Triple TheTriple(TT);

    RM = TheTriple.isOSDarwin() ? Reloc::PIC_ : Reloc::DynamicNoPIC;
  }
  X->InitMCCodeGenInfo(RM, CM);
  return X;
}
