getSectionForConstant(
    const DataLayout &DL, SectionKind Kind, const Constant *C) const {
  if (IsConstantInSmallSection(DL, C, *TM))
    return SmallDataSection;


  return TargetLoweringObjectFileELF::getSectionForConstant(DL, Kind, C);
}
