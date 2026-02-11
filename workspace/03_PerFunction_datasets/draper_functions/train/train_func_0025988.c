print(raw_ostream &OS) const {
  if (getLanguage())
    OS << " [" << dwarf::LanguageString(getLanguage()) << "] ";

  OS << " [" << getDirectory() << "/" << getFilename() << "]";
}
