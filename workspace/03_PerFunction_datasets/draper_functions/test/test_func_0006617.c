isMoveInstr(const TargetRegisterInfo &tri, const MachineInstr *MI,
                        unsigned &Src, unsigned &Dst,
                        unsigned &SrcSub, unsigned &DstSub) {
  if (MI->isCopy()) {
    Dst = MI->getOperand(0).getReg();
    DstSub = MI->getOperand(0).getSubReg();
    Src = MI->getOperand(1).getReg();
    SrcSub = MI->getOperand(1).getSubReg();
  } else if (MI->isSubregToReg()) {
    Dst = MI->getOperand(0).getReg();
    DstSub = compose(tri, MI->getOperand(0).getSubReg(),
                     MI->getOperand(3).getImm());
    Src = MI->getOperand(2).getReg();
    SrcSub = MI->getOperand(2).getSubReg();
  } else
    return false;
  return true;
}
