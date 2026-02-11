getFD(StringRef Filename, std::error_code &EC,
                 sys::fs::OpenFlags Flags) {


  if (Filename == "-") {
    EC = std::error_code();


    if (!(Flags & sys::fs::F_Text))
      sys::ChangeStdoutToBinary();
    return STDOUT_FILENO;
  }

  int FD;
  EC = sys::fs::openFileForWrite(Filename, FD, Flags);
  if (EC)
    return -1;

  return FD;
}
