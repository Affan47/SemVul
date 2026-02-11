WriteFileHeader(const COFF::header &Header) {
  if (UseBigObj) {
    writeLE16(COFF::IMAGE_FILE_MACHINE_UNKNOWN);
    writeLE16(0xFFFF);
    writeLE16(COFF::BigObjHeader::MinBigObjectVersion);
    writeLE16(Header.Machine);
    writeLE32(Header.TimeDateStamp);
    writeBytes(StringRef(COFF::BigObjMagic, sizeof(COFF::BigObjMagic)));
    writeLE32(0);
    writeLE32(0);
    writeLE32(0);
    writeLE32(0);
    writeLE32(Header.NumberOfSections);
    writeLE32(Header.PointerToSymbolTable);
    writeLE32(Header.NumberOfSymbols);
  } else {
    writeLE16(Header.Machine);
    writeLE16(static_cast<int16_t>(Header.NumberOfSections));
    writeLE32(Header.TimeDateStamp);
    writeLE32(Header.PointerToSymbolTable);
    writeLE32(Header.NumberOfSymbols);
    writeLE16(Header.SizeOfOptionalHeader);
    writeLE16(Header.Characteristics);
  }
}
