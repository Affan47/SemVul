SendAllocateSpace(uint32_t Alignment, uint32_t Size) {
  if (!SendHeader(LLI_AllocateSpace)) {
    ErrorMsg += ", (RemoteTargetExternal::SendAllocateSpace)";
    return false;
  }

  AppendWrite((const void *)&Alignment, 4);
  AppendWrite((const void *)&Size, 4);

  if (!SendPayload()) {
    ErrorMsg += ", (RemoteTargetExternal::SendAllocateSpace)";
    return false;
  }
  return true;
}
