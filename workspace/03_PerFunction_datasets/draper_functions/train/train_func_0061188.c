EmitSectionLabels() {
  const TargetLoweringObjectFile &TLOF = Asm->getObjFileLowering();


  DwarfInfoSectionSym =
    EmitSectionSym(Asm, TLOF.getDwarfInfoSection(), "section_info");
  DwarfAbbrevSectionSym =
    EmitSectionSym(Asm, TLOF.getDwarfAbbrevSection(), "section_abbrev");
  EmitSectionSym(Asm, TLOF.getDwarfARangesSection());

  if (const MCSection *MacroInfo = TLOF.getDwarfMacroInfoSection())
    EmitSectionSym(Asm, MacroInfo);

  EmitSectionSym(Asm, TLOF.getDwarfLineSection(), "section_line");
  EmitSectionSym(Asm, TLOF.getDwarfLocSection());
  EmitSectionSym(Asm, TLOF.getDwarfPubNamesSection());
  EmitSectionSym(Asm, TLOF.getDwarfPubTypesSection());
  DwarfStrSectionSym =
    EmitSectionSym(Asm, TLOF.getDwarfStrSection(), "section_str");
  DwarfDebugRangeSectionSym = EmitSectionSym(Asm, TLOF.getDwarfRangesSection(),
                                             "debug_range");

  DwarfDebugLocSectionSym = EmitSectionSym(Asm, TLOF.getDwarfLocSection(),
                                           "section_debug_loc");

  TextSectionSym = EmitSectionSym(Asm, TLOF.getTextSection(), "text_begin");
  EmitSectionSym(Asm, TLOF.getDataSection());
}
