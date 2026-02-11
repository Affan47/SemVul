ParseSubsection(const uint8_t *Data, uint32_t Length) {
  uint32_t Offset = sizeof(uint32_t);

  SW.printNumber("SectionLength", Length);

  const char *VendorName = reinterpret_cast<const char*>(Data + Offset);
  size_t VendorNameLength = std::strlen(VendorName);
  SW.printString("Vendor", StringRef(VendorName, VendorNameLength));
  Offset = Offset + VendorNameLength + 1;

  if (StringRef(VendorName, VendorNameLength).lower() != "aeabi")
    return;

  while (Offset < Length) {

    uint8_t Tag = Data[Offset];
    SW.printEnum("Tag", Tag, makeArrayRef(TagNames));
    Offset = Offset + sizeof(Tag);

    uint32_t Size =
      *reinterpret_cast<const support::ulittle32_t*>(Data + Offset);
    SW.printNumber("Size", Size);
    Offset = Offset + sizeof(Size);

    if (Size > Length) {
      errs() << "subsection length greater than section length\n";
      return;
    }

    StringRef ScopeName, IndexName;
    SmallVector<uint8_t, 8> Indicies;
    switch (Tag) {
    case ARMBuildAttrs::File:
      ScopeName = "FileAttributes";
      break;
    case ARMBuildAttrs::Section:
      ScopeName = "SectionAttributes";
      IndexName = "Sections";
      ParseIndexList(Data, Offset, Indicies);
      break;
    case ARMBuildAttrs::Symbol:
      ScopeName = "SymbolAttributes";
      IndexName = "Symbols";
      ParseIndexList(Data, Offset, Indicies);
      break;
    default:
      errs() << "unrecognised tag: 0x" << utohexstr(Tag) << '\n';
      return;
    }

    DictScope ASS(SW, ScopeName);

    if (!Indicies.empty())
      SW.printList(IndexName, Indicies);

    ParseAttributeList(Data, Offset, Length);
  }
}
