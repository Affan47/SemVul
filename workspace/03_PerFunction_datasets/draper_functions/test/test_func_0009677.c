indent(unsigned NumSpaces) {
  static const char Spaces[] = "                                "
                               "                                "
                               "                ";


  if (NumSpaces < array_lengthof(Spaces))
    return write(Spaces, NumSpaces);

  while (NumSpaces) {
    unsigned NumToWrite = std::min(NumSpaces,
                                   (unsigned)array_lengthof(Spaces)-1);
    write(Spaces, NumToWrite);
    NumSpaces -= NumToWrite;
  }
  return *this;
}
