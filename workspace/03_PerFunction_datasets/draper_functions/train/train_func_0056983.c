getLargestLegalSuperClass(const TargetRegisterClass *RC,
                                           const MachineFunction &MF) const {
  const PPCSubtarget &Subtarget = MF.getSubtarget<PPCSubtarget>();
  if (Subtarget.hasVSX()) {


    if (RC == &PPC::F8RCRegClass)
      return &PPC::VSFRCRegClass;
    else if (RC == &PPC::VRRCRegClass)
      return &PPC::VSRCRegClass;
    else if (RC == &PPC::F4RCRegClass && Subtarget.hasP8Vector())
      return &PPC::VSSRCRegClass;
  }

  return TargetRegisterInfo::getLargestLegalSuperClass(RC, MF);
}
