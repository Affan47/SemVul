ReadData(StringRef K, const unsigned char *D,
                                         offset_type N) {

  if (N % sizeof(uint64_t))
    return data_type();

  DataBuffer.clear();
  std::vector<uint64_t> CounterBuffer;

  using namespace support;
  const unsigned char *End = D + N;
  while (D < End) {

    if (D + sizeof(uint64_t) >= End)
      return data_type();
    uint64_t Hash = endian::readNext<uint64_t, little, unaligned>(D);


    uint64_t CountsSize = N / sizeof(uint64_t) - 1;

    if (FormatVersion != 1) {
      if (D + sizeof(uint64_t) > End)
        return data_type();
      CountsSize = endian::readNext<uint64_t, little, unaligned>(D);
    }

    if (D + CountsSize * sizeof(uint64_t) > End)
      return data_type();

    CounterBuffer.clear();
    CounterBuffer.reserve(CountsSize);
    for (uint64_t J = 0; J < CountsSize; ++J)
      CounterBuffer.push_back(endian::readNext<uint64_t, little, unaligned>(D));

    DataBuffer.emplace_back(K, Hash, std::move(CounterBuffer));


    if (FormatVersion > 2 && !ReadValueProfilingData(D, End)) {
      DataBuffer.clear();
      return data_type();
    }
  }
  return DataBuffer;
}
