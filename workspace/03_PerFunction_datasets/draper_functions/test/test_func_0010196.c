allocate(const std::set<uint64_t> &Bits,
                                uint64_t BitSize, uint64_t &AllocByteOffset,
                                uint8_t &AllocMask) {

  unsigned Bit = 0;
  for (unsigned I = 1; I != BitsPerByte; ++I)
    if (BitAllocs[I] < BitAllocs[Bit])
      Bit = I;

  AllocByteOffset = BitAllocs[Bit];


  unsigned ReqSize = AllocByteOffset + BitSize;
  BitAllocs[Bit] = ReqSize;
  if (Bytes.size() < ReqSize)
    Bytes.resize(ReqSize);


  AllocMask = 1 << Bit;
  for (uint64_t B : Bits)
    Bytes[AllocByteOffset + B] |= AllocMask;
}
