copyImplicitOps(MachineFunction &MF,
                                   const MachineInstr *MI) {
  for (unsigned i = MI->getDesc().getNumOperands(), e = MI->getNumOperands();
       i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if ((MO.isReg() && MO.isImplicit()) || MO.isRegMask())
      addOperand(MF, MO);
  }
}
