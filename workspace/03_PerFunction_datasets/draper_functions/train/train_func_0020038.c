loadConstant(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator I,
                                        DebugLoc DL,
                                        unsigned Reg,
                                        int value) const {
  if (isInt<7>(value)) {
    BuildMI(MBB, I, DL, TII.get(BF::LOADimm7), Reg).addImm(value);
    return;
  }

  if (isUInt<16>(value)) {
    BuildMI(MBB, I, DL, TII.get(BF::LOADuimm16), Reg).addImm(value);
    return;
  }

  if (isInt<16>(value)) {
    BuildMI(MBB, I, DL, TII.get(BF::LOADimm16), Reg).addImm(value);
    return;
  }


  BuildMI(MBB, I, DL,
          TII.get(BF::LOAD16i), getSubReg(Reg, BF::hi16))
    .addImm((value >> 16) & 0xffff)
    .addReg(Reg, RegState::ImplicitDefine);
  BuildMI(MBB, I, DL,
          TII.get(BF::LOAD16i), getSubReg(Reg, BF::lo16))
    .addImm(value & 0xffff)
    .addReg(Reg, RegState::ImplicitKill)
    .addReg(Reg, RegState::ImplicitDefine);
}
