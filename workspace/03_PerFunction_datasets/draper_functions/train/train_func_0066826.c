canMoveMemTo(MachineInstr *TheI, MachineInstr *ToI,
      bool IsDown) {
  bool IsLoad = TheI->mayLoad(), IsStore = TheI->mayStore();
  if (!IsLoad && !IsStore)
    return true;
  if (HII->areMemAccessesTriviallyDisjoint(TheI, ToI))
    return true;
  if (TheI->hasUnmodeledSideEffects())
    return false;

  MachineBasicBlock::iterator StartI = IsDown ? TheI : ToI;
  MachineBasicBlock::iterator EndI = IsDown ? ToI : TheI;
  bool Ordered = TheI->hasOrderedMemoryRef();


  for (MachineBasicBlock::iterator I = std::next(StartI); I != EndI; ++I) {
    MachineInstr *MI = &*I;
    if (MI->hasUnmodeledSideEffects())
      return false;
    bool L = MI->mayLoad(), S = MI->mayStore();
    if (!L && !S)
      continue;
    if (Ordered && MI->hasOrderedMemoryRef())
      return false;

    bool Conflict = (L && IsStore) || S;
    if (Conflict)
      return false;
  }
  return true;
}
