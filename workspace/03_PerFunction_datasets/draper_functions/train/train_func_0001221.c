emitMSACBranchPseudo(MachineInstr *MI, MachineBasicBlock *BB,
                     unsigned BranchOp) const{


  MachineRegisterInfo &RegInfo = BB->getParent()->getRegInfo();
  const TargetInstrInfo *TII = Subtarget.getInstrInfo();
  const TargetRegisterClass *RC = &Mips::GPR32RegClass;
  DebugLoc DL = MI->getDebugLoc();
  const BasicBlock *LLVM_BB = BB->getBasicBlock();
  MachineFunction::iterator It = std::next(MachineFunction::iterator(BB));
  MachineFunction *F = BB->getParent();
  MachineBasicBlock *FBB = F->CreateMachineBasicBlock(LLVM_BB);
  MachineBasicBlock *TBB = F->CreateMachineBasicBlock(LLVM_BB);
  MachineBasicBlock *Sink  = F->CreateMachineBasicBlock(LLVM_BB);
  F->insert(It, FBB);
  F->insert(It, TBB);
  F->insert(It, Sink);


  Sink->splice(Sink->begin(), BB, std::next(MachineBasicBlock::iterator(MI)),
               BB->end());
  Sink->transferSuccessorsAndUpdatePHIs(BB);


  BB->addSuccessor(FBB);
  BB->addSuccessor(TBB);
  FBB->addSuccessor(Sink);
  TBB->addSuccessor(Sink);


  BuildMI(BB, DL, TII->get(BranchOp))
    .addReg(MI->getOperand(1).getReg())
    .addMBB(TBB);


  unsigned RD1 = RegInfo.createVirtualRegister(RC);
  BuildMI(*FBB, FBB->end(), DL, TII->get(Mips::ADDiu), RD1)
    .addReg(Mips::ZERO).addImm(0);
  BuildMI(*FBB, FBB->end(), DL, TII->get(Mips::B)).addMBB(Sink);


  unsigned RD2 = RegInfo.createVirtualRegister(RC);
  BuildMI(*TBB, TBB->end(), DL, TII->get(Mips::ADDiu), RD2)
    .addReg(Mips::ZERO).addImm(1);


  BuildMI(*Sink, Sink->begin(), DL, TII->get(Mips::PHI),
          MI->getOperand(0).getReg())
    .addReg(RD1).addMBB(FBB).addReg(RD2).addMBB(TBB);

  MI->eraseFromParent();
  return Sink;
}
