loadData(uint64_t Address, const void *Data, size_t Size) {
  DEBUG(dbgs() << "Message [load data] addr: 0x" << format("%llx", Address) <<
                  ", size: " << Size << "\n");
  if (!SendLoadSection(Address, Data, (uint32_t)Size, false)) {
    ErrorMsg += ", (RemoteTargetExternal::loadData)";
    return false;
  }
  int Status = LLI_Status_Success;
  if (!Receive(LLI_LoadResult, Status)) {
    ErrorMsg += ", (RemoteTargetExternal::loadData)";
    return false;
  }
  if (Status == LLI_Status_IncompleteMsg) {
    ErrorMsg += "incomplete load data, (RemoteTargetExternal::loadData)";
    return false;
  }
  if (Status == LLI_Status_NotAllocated) {
    ErrorMsg += "data memory not allocated, (RemoteTargetExternal::loadData)";
    return false;
  }
  DEBUG(dbgs() << "Message [load data] complete\n");
  return true;
}
