getPreviousVector(MachineBasicBlock::iterator I)
      const {
    DenseMap<unsigned, unsigned> Result;
    I--;
    if (!TII->isALUInstr(I->getOpcode()) && !I->isBundle())
      return Result;
    MachineBasicBlock::instr_iterator BI = I.getInstrIterator();
    if (I->isBundle())
      BI++;
    int LastDstChan = -1;
    do {
      bool isTrans = false;
      int BISlot = getSlot(&*BI);
      if (LastDstChan >= BISlot)
        isTrans = true;
      LastDstChan = BISlot;
      if (TII->isPredicated(&*BI))
        continue;
      int OperandIdx = TII->getOperandIdx(BI->getOpcode(), AMDGPU::OpName::write);
      if (OperandIdx > -1 && BI->getOperand(OperandIdx).getImm() == 0)
        continue;
      int DstIdx = TII->getOperandIdx(BI->getOpcode(), AMDGPU::OpName::dst);
      if (DstIdx == -1) {
        continue;
      }
      unsigned Dst = BI->getOperand(DstIdx).getReg();
      if (isTrans || TII->isTransOnly(&*BI)) {
        Result[Dst] = AMDGPU::PS;
        continue;
      }
      if (BI->getOpcode() == AMDGPU::DOT4_r600 ||
          BI->getOpcode() == AMDGPU::DOT4_eg) {
        Result[Dst] = AMDGPU::PV_X;
        continue;
      }
      if (Dst == AMDGPU::OQAP) {
        continue;
      }
      unsigned PVReg = 0;
      switch (TRI.getHWRegChan(Dst)) {
      case 0:
        PVReg = AMDGPU::PV_X;
        break;
      case 1:
        PVReg = AMDGPU::PV_Y;
        break;
      case 2:
        PVReg = AMDGPU::PV_Z;
        break;
      case 3:
        PVReg = AMDGPU::PV_W;
        break;
      default:
        llvm_unreachable("Invalid Chan");
      }
      Result[Dst] = PVReg;
    } while ((++BI)->isBundledWithPred());
    return Result;
  }
