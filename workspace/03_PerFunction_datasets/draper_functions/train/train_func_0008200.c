printRuntimeFunction(const Context &Ctx,
                                  const coff_section *Section,
                                  uint64_t SectionOffset,
                                  const RuntimeFunction &RF) {
  DictScope RFS(SW, "RuntimeFunction");
  printRuntimeFunctionEntry(Ctx, Section, SectionOffset, RF);

  const coff_section *XData;
  uint64_t Offset;
  resolveRelocation(Ctx, Section, SectionOffset + 8, XData, Offset);

  ArrayRef<uint8_t> Contents;
  error(Ctx.COFF.getSectionContents(XData, Contents));
  if (Contents.empty())
    return;

  Offset = Offset + RF.UnwindInfoOffset;
  if (Offset > Contents.size())
    return;

  const auto UI = reinterpret_cast<const UnwindInfo*>(Contents.data() + Offset);
  printUnwindInfo(Ctx, XData, Offset, *UI);
}
