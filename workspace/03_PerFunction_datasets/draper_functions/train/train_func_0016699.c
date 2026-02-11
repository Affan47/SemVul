getCalleeSavedRegs(const MachineFunction *MF) const {
  const TargetFrameLowering *TFI = MF->getTarget().getFrameLowering();
  const Function* F = MF->getFunction();
  static const unsigned CalleeSavedRegs[] = {
    MSP430::FPW, MSP430::R5W, MSP430::R6W, MSP430::R7W,
    MSP430::R8W, MSP430::R9W, MSP430::R10W, MSP430::R11W,
    0
  };
  static const unsigned CalleeSavedRegsFP[] = {
    MSP430::R5W, MSP430::R6W, MSP430::R7W,
    MSP430::R8W, MSP430::R9W, MSP430::R10W, MSP430::R11W,
    0
  };
  static const unsigned CalleeSavedRegsIntr[] = {
    MSP430::FPW,  MSP430::R5W,  MSP430::R6W,  MSP430::R7W,
    MSP430::R8W,  MSP430::R9W,  MSP430::R10W, MSP430::R11W,
    MSP430::R12W, MSP430::R13W, MSP430::R14W, MSP430::R15W,
    0
  };
  static const unsigned CalleeSavedRegsIntrFP[] = {
    MSP430::R5W,  MSP430::R6W,  MSP430::R7W,
    MSP430::R8W,  MSP430::R9W,  MSP430::R10W, MSP430::R11W,
    MSP430::R12W, MSP430::R13W, MSP430::R14W, MSP430::R15W,
    0
  };

  if (TFI->hasFP(*MF))
    return (F->getCallingConv() == CallingConv::MSP430_INTR ?
            CalleeSavedRegsIntrFP : CalleeSavedRegsFP);
  else
    return (F->getCallingConv() == CallingConv::MSP430_INTR ?
            CalleeSavedRegsIntr : CalleeSavedRegs);

}
