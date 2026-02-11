ParseSectionSwitch(StringRef Section, unsigned Type,
                                      unsigned Flags, SectionKind Kind) {
  const MCExpr *Subsection = nullptr;
  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    if (getParser().parseExpression(Subsection))
      return true;
  }

  getStreamer().SwitchSection(getContext().getELFSection(Section, Type, Flags),
                              Subsection);

  return false;
}
