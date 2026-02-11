SelectSectionForGlobal(
    const GlobalValue *GV, SectionKind Kind, Mangler &Mang,
    const TargetMachine &TM) const {
  unsigned Flags = getELFSectionFlags(Kind);


  bool EmitUniqueSection = false;
  if (!(Flags & ELF::SHF_MERGE) && !Kind.isCommon()) {
    if (Kind.isText())
      EmitUniqueSection = TM.getFunctionSections();
    else
      EmitUniqueSection = TM.getDataSections();
  }
  EmitUniqueSection |= GV->hasComdat();

  return selectELFSectionForGlobal(getContext(), GV, Kind, Mang, TM,
                                   EmitUniqueSection, Flags, &NextUniqueID);
}
