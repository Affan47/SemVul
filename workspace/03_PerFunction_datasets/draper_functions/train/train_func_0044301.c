getMCRDeprecationInfo(MCInst &MI, const MCSubtargetInfo &STI,
                                  std::string &Info) {
  if (STI.getFeatureBits()[llvm::ARM::HasV7Ops] &&
      (MI.getOperand(0).isImm() && MI.getOperand(0).getImm() == 15) &&
      (MI.getOperand(1).isImm() && MI.getOperand(1).getImm() == 0) &&


      (MI.getOperand(3).isImm() && MI.getOperand(3).getImm() == 7)) {
    if ((MI.getOperand(5).isImm() && MI.getOperand(5).getImm() == 4)) {
      if (MI.getOperand(4).isImm() && MI.getOperand(4).getImm() == 5) {
        Info = "deprecated since v7, use 'isb'";
        return true;
      }


      if (MI.getOperand(4).isImm() && MI.getOperand(4).getImm() == 10) {
        Info = "deprecated since v7, use 'dsb'";
        return true;
      }
    }


    if (MI.getOperand(4).isImm() && MI.getOperand(4).getImm() == 10 &&
        (MI.getOperand(5).isImm() && MI.getOperand(5).getImm() == 5)) {
      Info = "deprecated since v7, use 'dmb'";
      return true;
    }
  }
  return false;
}
