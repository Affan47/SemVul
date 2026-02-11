printOptionInfo(const Option &O,
                                          size_t GlobalWidth) const {
  if (O.hasArgStr()) {
    outs() << "  -" << O.ArgStr;
    printHelpStr(O.HelpStr, GlobalWidth, std::strlen(O.ArgStr) + 6);

    for (unsigned i = 0, e = getNumOptions(); i != e; ++i) {
      size_t NumSpaces = GlobalWidth - strlen(getOption(i)) - 8;
      outs() << "    =" << getOption(i);
      outs().indent(NumSpaces) << " -   " << getDescription(i) << '\n';
    }
  } else {
    if (O.HelpStr[0])
      outs() << "  " << O.HelpStr << '\n';
    for (unsigned i = 0, e = getNumOptions(); i != e; ++i) {
      const char *Option = getOption(i);
      outs() << "    -" << Option;
      printHelpStr(getDescription(i), GlobalWidth, std::strlen(Option) + 8);
    }
  }
}
