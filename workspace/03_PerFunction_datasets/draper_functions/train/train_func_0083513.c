ProcessFailure(sys::Path ProgPath, const char** Args,
                                  unsigned Timeout = 0,
                                  unsigned MemoryLimit = 0) {
  std::ostringstream OS;
  OS << "\nError running tool:\n ";
  for (const char **Arg = Args; *Arg; ++Arg)
    OS << " " << *Arg;
  OS << "\n";


  sys::Path ErrorFilename("bugpoint.program_error_messages");
  std::string ErrMsg;
  if (ErrorFilename.makeUnique(true, &ErrMsg)) {
    errs() << "Error making unique filename: " << ErrMsg << "\n";
    exit(1);
  }
  RunProgramWithTimeout(ProgPath, Args, sys::Path(""), ErrorFilename,
                        ErrorFilename, Timeout, MemoryLimit);


  std::ifstream ErrorFile(ErrorFilename.c_str());
  if (ErrorFile) {
    std::copy(std::istreambuf_iterator<char>(ErrorFile),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(OS));
    ErrorFile.close();
  }

  ErrorFilename.eraseFromDisk();
  return OS.str();
}
