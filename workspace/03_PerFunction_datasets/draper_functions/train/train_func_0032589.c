translateCopy(MachineInstr *MI) {
  unsigned DstReg = MI->getOperand(0).getReg();
  unsigned SrcReg = MI->getOperand(1).getReg();

  if (DstReg == X86::ST0) {
    MI->setDesc(TII->get(X86::FpSET_ST0_80));
    MI->RemoveOperand(0);
    return true;
  }
  if (DstReg == X86::ST1) {
    MI->setDesc(TII->get(X86::FpSET_ST1_80));
    MI->RemoveOperand(0);
    return true;
  }
  if (SrcReg == X86::ST0) {
    MI->setDesc(TII->get(X86::FpGET_ST0_80));
    return true;
  }
  if (SrcReg == X86::ST1) {
    MI->setDesc(TII->get(X86::FpGET_ST1_80));
    return true;
  }
  if (X86::RFP80RegClass.contains(DstReg, SrcReg)) {
    MI->setDesc(TII->get(X86::MOV_Fp8080));
    return true;
  }
  return false;
}
