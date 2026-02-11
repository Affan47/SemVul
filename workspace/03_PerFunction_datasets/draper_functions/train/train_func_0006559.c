getELFKindForNamedSection(StringRef Name, SectionKind K) {
  if (Name.empty() || Name[0] != '.') return K;


  if (Name == ".bss" ||
      Name.startswith(".bss.") ||
      Name.startswith(".gnu.linkonce.b.") ||
      Name.startswith(".llvm.linkonce.b.") ||
      Name == ".sbss" ||
      Name.startswith(".sbss.") ||
      Name.startswith(".gnu.linkonce.sb.") ||
      Name.startswith(".llvm.linkonce.sb."))
    return SectionKind::getBSS();

  if (Name == ".tdata" ||
      Name.startswith(".tdata.") ||
      Name.startswith(".gnu.linkonce.td.") ||
      Name.startswith(".llvm.linkonce.td."))
    return SectionKind::getThreadData();

  if (Name == ".tbss" ||
      Name.startswith(".tbss.") ||
      Name.startswith(".gnu.linkonce.tb.") ||
      Name.startswith(".llvm.linkonce.tb."))
    return SectionKind::getThreadBSS();

  return K;
}
