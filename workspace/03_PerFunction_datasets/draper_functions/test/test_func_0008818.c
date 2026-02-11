isNoReturnDef(const MachineOperand &MO) {

  const MachineInstr &MI = *MO.getParent();
  if (!MI.isCall())
    return false;
  const MachineBasicBlock &MBB = *MI.getParent();
  if (!MBB.succ_empty())
    return false;
  const MachineFunction &MF = *MBB.getParent();


  if (MF.getFunction()->hasFnAttribute(Attribute::UWTable))
    return false;
  const Function *Called = getCalledFunction(MI);
  return !(Called == nullptr || !Called->hasFnAttribute(Attribute::NoReturn) ||
           !Called->hasFnAttribute(Attribute::NoUnwind));
}
