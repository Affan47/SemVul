EmitRegisterName(int64_t Register) {
  if (InstPrinter && !MAI.useDwarfRegNumForCFI()) {
    const MCRegisterInfo &MRI = getContext().getRegisterInfo();
    unsigned LLVMRegister = MRI.getLLVMRegNum(Register, true);
    InstPrinter->printRegName(OS, LLVMRegister);
  } else {
    OS << Register;
  }
}
