WriteSectionHeader(MCAssembler &Asm,
                                         const GroupMapTy &GroupMap,
                                         const MCAsmLayout &Layout,
                                      const SectionIndexMapTy &SectionIndexMap,
                                   const SectionOffsetMapTy &SectionOffsetMap) {
  const unsigned NumSections = Asm.size() + 1;

  std::vector<const MCSectionELF*> Sections;
  Sections.resize(NumSections - 1);

  for (SectionIndexMapTy::const_iterator i=
         SectionIndexMap.begin(), e = SectionIndexMap.end(); i != e; ++i) {
    const std::pair<const MCSectionELF*, uint32_t> &p = *i;
    Sections[p.second - 1] = p.first;
  }


  uint64_t FirstSectionSize =
    NumSections >= ELF::SHN_LORESERVE ? NumSections : 0;
  uint32_t FirstSectionLink =
    ShstrtabIndex >= ELF::SHN_LORESERVE ? ShstrtabIndex : 0;
  WriteSecHdrEntry(0, 0, 0, 0, 0, FirstSectionSize, FirstSectionLink, 0, 0, 0);

  for (unsigned i = 0; i < NumSections - 1; ++i) {
    const MCSectionELF &Section = *Sections[i];
    const MCSectionData &SD = Asm.getOrCreateSectionData(Section);
    uint32_t GroupSymbolIndex;
    if (Section.getType() != ELF::SHT_GROUP)
      GroupSymbolIndex = 0;
    else
      GroupSymbolIndex = getSymbolIndexInSymbolTable(Asm,
                                                     GroupMap.lookup(&Section));

    uint64_t Size = GetSectionAddressSize(Layout, SD);

    WriteSection(Asm, SectionIndexMap, GroupSymbolIndex,
                 SectionOffsetMap.lookup(&Section), Size,
                 SD.getAlignment(), Section);
  }
}
