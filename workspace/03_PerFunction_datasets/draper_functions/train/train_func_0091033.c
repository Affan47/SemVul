EmitInstruction(const MCInst &Inst,
                       const MCSubtargetInfo &STI) override {

    if (isIndirectJump(Inst)) {
      if (PendingCall)
        report_fatal_error("Dangerous instruction in branch delay slot!");
      sandboxIndirectJump(Inst, STI);
      return;
    }


    unsigned AddrIdx;
    bool IsStore;
    bool IsMemAccess = isBasePlusOffsetMemoryAccess(Inst.getOpcode(), &AddrIdx,
                                                    &IsStore);
    bool IsSPFirstOperand = isStackPointerFirstOperand(Inst);
    if (IsMemAccess || IsSPFirstOperand) {
      bool MaskBefore = (IsMemAccess
                         && baseRegNeedsLoadStoreMask(Inst.getOperand(AddrIdx)
                                                          .getReg()));
      bool MaskAfter = IsSPFirstOperand && !IsStore;
      if (MaskBefore || MaskAfter) {
        if (PendingCall)
          report_fatal_error("Dangerous instruction in branch delay slot!");
        sandboxLoadStoreStackChange(Inst, AddrIdx, STI, MaskBefore, MaskAfter);
        return;
      }

    }


    bool IsIndirectCall;
    if (isCall(Inst, &IsIndirectCall)) {
      if (PendingCall)
        report_fatal_error("Dangerous instruction in branch delay slot!");


      EmitBundleLock(true);
      if (IsIndirectCall) {
        unsigned TargetReg = Inst.getOperand(1).getReg();
        emitMask(TargetReg, IndirectBranchMaskReg, STI);
      }
      MipsELFStreamer::EmitInstruction(Inst, STI);
      PendingCall = true;
      return;
    }
    if (PendingCall) {

      MipsELFStreamer::EmitInstruction(Inst, STI);
      EmitBundleUnlock();
      PendingCall = false;
      return;
    }


    MipsELFStreamer::EmitInstruction(Inst, STI);
  }
