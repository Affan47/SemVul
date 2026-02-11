LLVMPrintModuleToFile(LLVMModuleRef M, const char *Filename,
                               char **ErrorMessage) {
  std::error_code EC;
  raw_fd_ostream dest(Filename, EC, sys::fs::F_Text);
  if (EC) {
    *ErrorMessage = strdup(EC.message().c_str());
    return true;
  }

  unwrap(M)->print(dest, nullptr);

  dest.close();

  if (dest.has_error()) {
    *ErrorMessage = strdup("Error printing to file");
    return true;
  }

  return false;
}
