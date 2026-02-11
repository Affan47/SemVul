EndCf(MachineInstr &MI) {
  MachineBasicBlock &MBB = *MI.getParent();
  DebugLoc DL = MI.getDebugLoc();
  unsigned Reg = MI.getOperand(0).getReg();

  BuildMI(MBB, MBB.getFirstNonPHI(), DL,
          TII->get(AMDGPU::S_OR_B64), AMDGPU::EXEC)
          .addReg(AMDGPU::EXEC)
          .addReg(Reg);

  MI.eraseFromParent();
}
