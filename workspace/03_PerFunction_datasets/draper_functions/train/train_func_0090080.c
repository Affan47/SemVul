runOnMachineFunction(MachineFunction &Fn) {
  MF = &Fn;
  STI = &static_cast<const ARMSubtarget &>(Fn.getSubtarget());
  TL = STI->getTargetLowering();
  AFI = Fn.getInfo<ARMFunctionInfo>();
  TII = STI->getInstrInfo();
  TRI = STI->getRegisterInfo();

  RegClassInfoValid = false;
  isThumb2 = AFI->isThumb2Function();
  isThumb1 = AFI->isThumbFunction() && !isThumb2;

  bool Modified = false;
  for (MachineFunction::iterator MFI = Fn.begin(), E = Fn.end(); MFI != E;
       ++MFI) {
    MachineBasicBlock &MBB = *MFI;
    Modified |= LoadStoreMultipleOpti(MBB);
    if (STI->hasV5TOps())
      Modified |= MergeReturnIntoLDM(MBB);
  }

  Allocator.DestroyAll();
  return Modified;
}
