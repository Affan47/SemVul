encodeVirtualRegister(unsigned Reg) {
  if (TargetRegisterInfo::isVirtualRegister(Reg)) {
    const TargetRegisterClass *RC = MRI->getRegClass(Reg);

    DenseMap<unsigned, unsigned> &RegMap = VRegMapping[RC];
    unsigned RegNum = RegMap[Reg];


    unsigned Ret = 0;
    if (RC == &NVPTX::Int1RegsRegClass) {
      Ret = (1 << 28);
    } else if (RC == &NVPTX::Int16RegsRegClass) {
      Ret = (2 << 28);
    } else if (RC == &NVPTX::Int32RegsRegClass) {
      Ret = (3 << 28);
    } else if (RC == &NVPTX::Int64RegsRegClass) {
      Ret = (4 << 28);
    } else if (RC == &NVPTX::Float32RegsRegClass) {
      Ret = (5 << 28);
    } else if (RC == &NVPTX::Float64RegsRegClass) {
      Ret = (6 << 28);
    } else {
      report_fatal_error("Bad register class");
    }


    Ret |= (RegNum & 0x0FFFFFFF);
    return Ret;
  } else {


    return Reg & 0x0FFFFFFF;
  }
}
