getSectionForConstant(SectionKind Kind) const {
  if (Kind.isReadOnly() && ReadOnlySection != 0)
    return ReadOnlySection;

  return DataSection;
}
