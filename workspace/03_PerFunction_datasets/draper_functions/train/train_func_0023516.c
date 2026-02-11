print(raw_ostream &OS) const {
  StringRef Res = getName();
  if (!Res.empty())
    OS << " [" << Res << "] ";

  unsigned Tag = getTag();
  OS << " [" << dwarf::TagString(Tag) << "] ";


  OS << " [" << getLineNumber() << "] ";

  if (isLocalToUnit())
    OS << " [local] ";

  if (isDefinition())
    OS << " [def] ";

  OS << "\n";
}
