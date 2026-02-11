writeProgramToFile(const std::string &Filename,
                                   const Module *M) const {
  std::string ErrInfo;
  tool_output_file Out(Filename.c_str(), ErrInfo,
                       raw_fd_ostream::F_Binary);
  if (ErrInfo.empty()) {
    WriteBitcodeToFile(M, Out.os());
    Out.os().close();
    if (!Out.os().has_error()) {
      Out.keep();
      return false;
    }
  }
  Out.os().clear_error();
  return true;
}
