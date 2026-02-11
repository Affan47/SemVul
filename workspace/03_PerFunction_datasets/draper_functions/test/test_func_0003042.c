ReadValueProfilingData(
    const unsigned char *&D, const unsigned char *const End) {

  using namespace support;

  if (D + sizeof(uint64_t) > End)
    return false;
  uint64_t ValueKindCount = endian::readNext<uint64_t, little, unaligned>(D);

  InstrProfRecord &ProfRecord = DataBuffer.back();
  for (uint32_t Kind = 0; Kind < ValueKindCount; ++Kind) {


    if (D + 2 * sizeof(uint64_t) > End)
      return false;

    uint64_t ValueKind = endian::readNext<uint64_t, little, unaligned>(D);
    uint64_t ValueSiteCount = endian::readNext<uint64_t, little, unaligned>(D);

    ProfRecord.reserveSites(ValueKind, ValueSiteCount);

    for (uint64_t VSite = 0; VSite < ValueSiteCount; ++VSite) {

      if (D + sizeof(uint64_t) > End)
        return false;

      uint64_t ValueDataCount =
          endian::readNext<uint64_t, little, unaligned>(D);


      if (D + (ValueDataCount << 1) * sizeof(uint64_t) > End)
        return false;

      std::unique_ptr<InstrProfValueData[]> VDataPtr(
          ValueDataCount == 0 ? nullptr
                              : new InstrProfValueData[ValueDataCount]);

      for (uint64_t VCount = 0; VCount < ValueDataCount; ++VCount) {
        VDataPtr[VCount].Value =
            endian::readNext<uint64_t, little, unaligned>(D);
        VDataPtr[VCount].Count =
            endian::readNext<uint64_t, little, unaligned>(D);
      }
      ProfRecord.addValueData(ValueKind, VSite, VDataPtr.get(), ValueDataCount,
                              &HashKeys);
    }
  }
  return true;
}
