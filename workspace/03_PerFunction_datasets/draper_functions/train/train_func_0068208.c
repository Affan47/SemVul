isNewValueJump(const MachineInstr *MI) const {
  if (isNewValue(MI) && isBranch(MI))
    return true;
  return false;
}
