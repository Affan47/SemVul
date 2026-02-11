createInsertSubreg(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator InsertBefore,
                                   DebugLoc DL, unsigned DReg, unsigned Lane,
                                   unsigned ToInsert) {
  unsigned Out = MRI->createVirtualRegister(&ARM::DPR_VFP2RegClass);
  BuildMI(MBB,
          InsertBefore,
          DL,
          TII->get(TargetOpcode::INSERT_SUBREG), Out)
    .addReg(DReg)
    .addReg(ToInsert)
    .addImm(Lane);

  return Out;
}
