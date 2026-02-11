ComputeFragmentSize(const MCAsmLayout &Layout,
                                          const MCFragment &F) const {
  switch (F.getKind()) {
  case MCFragment::FT_Data:
    return cast<MCDataFragment>(F).getContents().size();
  case MCFragment::FT_Fill:
    return cast<MCFillFragment>(F).getSize();
  case MCFragment::FT_Inst:
    return cast<MCInstFragment>(F).getInstSize();

  case MCFragment::FT_LEB:
    return cast<MCLEBFragment>(F).getContents().size();

  case MCFragment::FT_Align: {
    const MCAlignFragment &AF = cast<MCAlignFragment>(F);
    unsigned Offset = Layout.getFragmentOffset(&AF);
    unsigned Size = OffsetToAlignment(Offset, AF.getAlignment());
    if (Size > AF.getMaxBytesToEmit())
      return 0;
    return Size;
  }

  case MCFragment::FT_Org: {
    MCOrgFragment &OF = cast<MCOrgFragment>(F);
    int64_t TargetLocation;
    if (!OF.getOffset().EvaluateAsAbsolute(TargetLocation, Layout))
      report_fatal_error("expected assembly-time absolute expression");


    uint64_t FragmentOffset = Layout.getFragmentOffset(&OF);
    int64_t Size = TargetLocation - FragmentOffset;
    if (Size < 0 || Size >= 0x40000000)
      report_fatal_error("invalid .org offset '" + Twine(TargetLocation) +
                         "' (at offset '" + Twine(FragmentOffset) + "')");
    return Size;
  }

  case MCFragment::FT_Dwarf:
    return cast<MCDwarfLineAddrFragment>(F).getContents().size();
  case MCFragment::FT_DwarfFrame:
    return cast<MCDwarfCallFrameFragment>(F).getContents().size();
  }

  assert(0 && "invalid fragment kind");
  return 0;
}
