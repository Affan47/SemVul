SetRegister(MachineInstr *I, unsigned *TLSBaseAddrReg) {
      MachineFunction *MF = I->getParent()->getParent();
      const X86Subtarget &STI = MF->getSubtarget<X86Subtarget>();
      const bool is64Bit = STI.is64Bit();
      const X86InstrInfo *TII = STI.getInstrInfo();


      MachineRegisterInfo &RegInfo = MF->getRegInfo();
      *TLSBaseAddrReg = RegInfo.createVirtualRegister(is64Bit
                                                      ? &X86::GR64RegClass
                                                      : &X86::GR32RegClass);


      MachineInstr *Next = I->getNextNode();
      MachineInstr *Copy = BuildMI(*I->getParent(), Next, I->getDebugLoc(),
                                   TII->get(TargetOpcode::COPY),
                                   *TLSBaseAddrReg)
                                   .addReg(is64Bit ? X86::RAX : X86::EAX);

      return Copy;
    }
