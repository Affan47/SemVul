needsStackFrame(const MachineBasicBlock &MBB, const BitVector &CSR) {
    for (auto &I : MBB) {
      const MachineInstr *MI = &I;
      if (MI->isCall())
        return true;
      unsigned Opc = MI->getOpcode();
      switch (Opc) {
        case Hexagon::ALLOCA:
        case Hexagon::ALIGNA:
          return true;
        default:
          break;
      }

      for (const MachineOperand &MO : MI->operands()) {


        if (MO.isFI())
          return true;
        if (!MO.isReg())
          continue;
        unsigned R = MO.getReg();


        if (TargetRegisterInfo::isVirtualRegister(R))
          return true;
        if (CSR[R])
          return true;
      }
    }
    return false;
  }
