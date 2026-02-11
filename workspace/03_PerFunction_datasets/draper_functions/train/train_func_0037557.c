addImplicitDefUseOperands(MachineFunction &MF) {
  if (MCID->ImplicitDefs)
    for (const uint16_t *ImpDefs = MCID->getImplicitDefs(); *ImpDefs; ++ImpDefs)
      addOperand(MF, MachineOperand::CreateReg(*ImpDefs, true, true));
  if (MCID->ImplicitUses)
    for (const uint16_t *ImpUses = MCID->getImplicitUses(); *ImpUses; ++ImpUses)
      addOperand(MF, MachineOperand::CreateReg(*ImpUses, false, true));
}
