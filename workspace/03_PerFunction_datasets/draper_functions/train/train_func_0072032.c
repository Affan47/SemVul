AlignLoop(MachineFunction &MF, MachineLoop *L,
                                 unsigned Align) {
  bool Changed = false;


  for (MachineLoop::iterator I = L->begin(), E = L->end(); I != E; ++I)
    Changed |= AlignLoop(MF, *I, Align);

  L->getTopBlock()->setAlignment(Align);
  Changed = true;
  ++NumLoopsAligned;

  return Changed;
}
