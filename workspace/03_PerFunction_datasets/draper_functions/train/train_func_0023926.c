LoadFile(const char *Filename) {

  std::ifstream In(Filename);
  if (!In.good()) {
    errs() << "WARNING: Internalize couldn't load file '" << Filename
         << "'! Continuing as if it's empty.\n";
    return;
  }
  while (In) {
    std::string Symbol;
    In >> Symbol;
    if (!Symbol.empty())
      ExternalNames.insert(Symbol);
  }
}
