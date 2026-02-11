EmitDwarfLineTable(MCStreamer *MCOS,
                                      const MCSection *Section,
                                      const MCLineSection *LineSection) {
  unsigned FileNum = 1;
  unsigned LastLine = 1;
  unsigned Column = 0;
  unsigned Flags = DWARF2_LINE_DEFAULT_IS_STMT ? DWARF2_FLAG_IS_STMT : 0;
  unsigned Isa = 0;
  MCSymbol *LastLabel = NULL;


  for (MCLineSection::const_iterator
         it = LineSection->getMCLineEntries()->begin(),
         ie = LineSection->getMCLineEntries()->end(); it != ie; ++it) {

    if (FileNum != it->getFileNum()) {
      FileNum = it->getFileNum();
      MCOS->EmitIntValue(dwarf::DW_LNS_set_file, 1);
      MCOS->EmitULEB128IntValue(FileNum);
    }
    if (Column != it->getColumn()) {
      Column = it->getColumn();
      MCOS->EmitIntValue(dwarf::DW_LNS_set_column, 1);
      MCOS->EmitULEB128IntValue(Column);
    }
    if (Isa != it->getIsa()) {
      Isa = it->getIsa();
      MCOS->EmitIntValue(dwarf::DW_LNS_set_isa, 1);
      MCOS->EmitULEB128IntValue(Isa);
    }
    if ((it->getFlags() ^ Flags) & DWARF2_FLAG_IS_STMT) {
      Flags = it->getFlags();
      MCOS->EmitIntValue(dwarf::DW_LNS_negate_stmt, 1);
    }
    if (it->getFlags() & DWARF2_FLAG_BASIC_BLOCK)
      MCOS->EmitIntValue(dwarf::DW_LNS_set_basic_block, 1);
    if (it->getFlags() & DWARF2_FLAG_PROLOGUE_END)
      MCOS->EmitIntValue(dwarf::DW_LNS_set_prologue_end, 1);
    if (it->getFlags() & DWARF2_FLAG_EPILOGUE_BEGIN)
      MCOS->EmitIntValue(dwarf::DW_LNS_set_epilogue_begin, 1);

    int64_t LineDelta = static_cast<int64_t>(it->getLine()) - LastLine;
    MCSymbol *Label = it->getLabel();


    const MCAsmInfo &asmInfo = MCOS->getContext().getAsmInfo();
    MCOS->EmitDwarfAdvanceLineAddr(LineDelta, LastLabel, Label,
                                   asmInfo.getPointerSize());

    LastLine = it->getLine();
    LastLabel = Label;
  }


  MCOS->SwitchSection(Section);

  MCContext &context = MCOS->getContext();

  MCSymbol *SectionEnd = context.CreateTempSymbol();

  MCOS->EmitLabel(SectionEnd);


  MCOS->SwitchSection(context.getObjectFileInfo()->getDwarfLineSection());

  const MCAsmInfo &asmInfo = MCOS->getContext().getAsmInfo();
  MCOS->EmitDwarfAdvanceLineAddr(INT64_MAX, LastLabel, SectionEnd,
                                 asmInfo.getPointerSize());
}
