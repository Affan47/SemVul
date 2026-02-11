spillCalleeSavedRegisters(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        const std::vector<CalleeSavedInfo> &CSI,
                                        const TargetRegisterInfo *TRI) const {
  if (CSI.empty())
    return false;

  MachineFunction &MF = *MBB.getParent();
  ARMFunctionInfo *AFI = MF.getInfo<ARMFunctionInfo>();

  unsigned PushOpc = AFI->isThumbFunction() ? ARM::t2STMDB_UPD : ARM::STMDB_UPD;
  unsigned PushOneOpc = AFI->isThumbFunction() ?
    ARM::t2STR_PRE : ARM::STR_PRE_IMM;
  unsigned FltOpc = ARM::VSTMDDB_UPD;
  unsigned NumAlignedDPRCS2Regs = AFI->getNumAlignedDPRCS2Regs();
  emitPushInst(MBB, MI, CSI, PushOpc, PushOneOpc, false, &isARMArea1Register, 0,
               MachineInstr::FrameSetup);
  emitPushInst(MBB, MI, CSI, PushOpc, PushOneOpc, false, &isARMArea2Register, 0,
               MachineInstr::FrameSetup);
  emitPushInst(MBB, MI, CSI, FltOpc, 0, true, &isARMArea3Register,
               NumAlignedDPRCS2Regs, MachineInstr::FrameSetup);


  if (NumAlignedDPRCS2Regs)
    emitAlignedDPRCS2Spills(MBB, MI, NumAlignedDPRCS2Regs, CSI, TRI);

  return true;
}
