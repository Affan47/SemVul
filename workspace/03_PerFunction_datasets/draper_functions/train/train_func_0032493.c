InitMCObjectFileInfo(StringRef TT, Reloc::Model RM,
                                            CodeModel::Model CM,
                                            MCContext &ctx) {
  InitMCObjectFileInfo(Triple(TT), RM, CM, ctx);
}
