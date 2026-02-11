getNextRewritableSource(unsigned &SrcReg, unsigned &SrcSubReg,
                               unsigned &TrackReg,
                               unsigned &TrackSubReg) override {

    if (CurrentSrcIdx == 1)
      return false;

    CurrentSrcIdx = 1;
    const MachineOperand &MOExtractedReg = CopyLike.getOperand(1);
    SrcReg = MOExtractedReg.getReg();

    if (MOExtractedReg.getSubReg())
      return false;

    SrcSubReg = CopyLike.getOperand(2).getImm();


    const MachineOperand &MODef = CopyLike.getOperand(0);
    TrackReg = MODef.getReg();
    TrackSubReg = MODef.getSubReg();
    return true;
  }
