initJumpTableInfo(MachineJumpTableInfo *MJTI) {
  if (TheJIT->getJITInfo().hasCustomJumpTables())
    return;
  if (MJTI->getEntryKind() == MachineJumpTableInfo::EK_Inline)
    return;

  const std::vector<MachineJumpTableEntry> &JT = MJTI->getJumpTables();
  if (JT.empty()) return;

  unsigned NumEntries = 0;
  for (unsigned i = 0, e = JT.size(); i != e; ++i)
    NumEntries += JT[i].MBBs.size();

  unsigned EntrySize = MJTI->getEntrySize(*TheJIT->getTargetData());


  JumpTable = MJTI;
  JumpTableBase = allocateSpace(NumEntries * EntrySize,
                             MJTI->getEntryAlignment(*TheJIT->getTargetData()));
}
