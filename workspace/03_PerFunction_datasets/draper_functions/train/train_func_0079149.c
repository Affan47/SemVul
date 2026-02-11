SendExecute(uint64_t Addr) {
  if (!SendHeader(LLI_Execute)) {
    ErrorMsg += ", (RemoteTargetExternal::SendExecute)";
    return false;
  }

  AppendWrite((const void *)&Addr, 8);

  if (!SendPayload()) {
    ErrorMsg += ", (RemoteTargetExternal::SendExecute)";
    return false;
  }
  return true;
}
