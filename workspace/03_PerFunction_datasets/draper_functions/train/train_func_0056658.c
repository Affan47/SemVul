EmitCFIDefCfaRegister(int64_t Register) {
  MCStreamer::EmitCFIDefCfaRegister(Register);

  if (!UseCFI)
    return;

  OS << "\t.cfi_def_cfa_register ";
  EmitRegisterName(Register);
  EmitEOL();
}
