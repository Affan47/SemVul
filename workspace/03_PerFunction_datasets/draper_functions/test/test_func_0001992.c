compileProgram(const std::string &Bitcode, std::string *Error,
                         unsigned Timeout, unsigned MemoryLimit) {
  std::string OutputAsmFile;
  OutputCode(Bitcode, OutputAsmFile, *Error, Timeout, MemoryLimit);
  sys::fs::remove(OutputAsmFile);
}
