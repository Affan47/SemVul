LLVMWriteBitcodeToFile(LLVMModuleRef M, const char *Path) {
  std::error_code EC;
  raw_fd_ostream OS(Path, EC, sys::fs::F_None);

  if (EC)
    return -1;

  WriteBitcodeToFile(unwrap(M), OS);
  return 0;
}
