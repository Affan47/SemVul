dumpProcedureDataEntry(const COFFObjectFile &COFF,
                                     const SectionRef Section, unsigned Index,
                                     ArrayRef<uint8_t> Contents) {
  uint64_t Offset = PDataEntrySize * Index;
  const ulittle32_t *Data =
    reinterpret_cast<const ulittle32_t *>(Contents.data() + Offset);

  const RuntimeFunction Entry(Data);
  DictScope RFS(SW, "RuntimeFunction");
  if (Entry.Flag() == RuntimeFunctionFlag::RFF_Unpacked)
    return dumpUnpackedEntry(COFF, Section, Offset, Index, Entry);
  return dumpPackedEntry(COFF, Section, Offset, Index, Entry);
}
