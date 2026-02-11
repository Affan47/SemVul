runOnMachineBasicBlock(MachineBasicBlock &MBB) {
  bool Changed = false;
  const MipsSubtarget &STI = MBB.getParent()->getSubtarget<MipsSubtarget>();
  bool InMicroMipsMode = STI.inMicroMipsMode();
  const MipsInstrInfo *TII = STI.getInstrInfo();

  for (Iter I = MBB.begin(); I != MBB.end(); ++I) {
    if (!hasUnoccupiedSlot(&*I))
      continue;

    ++FilledSlots;
    Changed = true;


    if (!DisableDelaySlotFiller && (TM.getOptLevel() != CodeGenOpt::None)) {
      bool Filled = false;

      if (searchBackward(MBB, I)) {
        Filled = true;
      } else if (I->isTerminator()) {
        if (searchSuccBBs(MBB, I)) {
          Filled = true;
        }
      } else if (searchForward(MBB, I)) {
        Filled = true;
      }

      if (Filled) {

        MachineBasicBlock::instr_iterator DSI(I);

        if (InMicroMipsMode && TII->GetInstSizeInBytes(&*std::next(DSI)) == 2 &&
            DSI->isCall()) {


          DSI->setDesc(TII->get(getEquivalentCallShort(DSI->getOpcode())));
        }

        continue;
      }
    }


    unsigned Opcode = I->getOpcode();
    if (InMicroMipsMode) {
      switch (Opcode) {
        case Mips::BEQ:
        case Mips::BNE:
          if (((unsigned) I->getOperand(1).getReg()) == Mips::ZERO) {
            I = replaceWithCompactBranch(MBB, I, I->getDebugLoc());
            continue;
          }
          break;
        case Mips::JR:
        case Mips::PseudoReturn:
        case Mips::PseudoIndirectBranch:


          I = replaceWithCompactJump(MBB, I, I->getDebugLoc());
          continue;
        default:
          break;
      }
    }

    BuildMI(MBB, std::next(I), I->getDebugLoc(), TII->get(Mips::NOP));
    MIBundleBuilder(MBB, I, std::next(I, 2));
  }

  return Changed;
}
