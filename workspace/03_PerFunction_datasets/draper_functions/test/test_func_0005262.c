isPredicable(MachineInstr *MI) {
  if (HII->isPredicated(MI) || !HII->isPredicable(MI))
    return false;
  if (MI->hasUnmodeledSideEffects() || MI->mayStore())
    return false;

  bool HasDef = false;
  for (auto &Op : MI->operands()) {
    if (!Op.isReg() || !Op.isDef())
      continue;
    if (HasDef)
      return false;
    HasDef = true;
  }
  for (auto &Mo : MI->memoperands())
    if (Mo->isVolatile())
      return false;
  return true;
}
