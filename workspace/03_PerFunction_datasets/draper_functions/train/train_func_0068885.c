getOrCreateJumpTableInfo(unsigned EntryKind) {
  if (JumpTableInfo) return JumpTableInfo;

  JumpTableInfo = new (Allocator)
    MachineJumpTableInfo((MachineJumpTableInfo::JTEntryKind)EntryKind);
  return JumpTableInfo;
}
