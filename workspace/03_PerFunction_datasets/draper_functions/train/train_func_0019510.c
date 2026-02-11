insertDefsUses(MachineBasicBlock::iterator MI,
                            SmallSet<unsigned, 32>& RegDefs,
                            SmallSet<unsigned, 32>& RegUses)
{
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg())
      continue;

    unsigned Reg = MO.getReg();
    if (Reg == 0)
      continue;
    if (MO.isDef())
      RegDefs.insert(Reg);
    if (MO.isUse()) {


      if (MO.isImplicit() && MI->getOpcode() == SP::RETL)
        continue;
      RegUses.insert(Reg);
    }
  }
}
