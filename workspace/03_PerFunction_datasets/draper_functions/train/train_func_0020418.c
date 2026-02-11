dumpHeader(raw_ostream &OS) const override {
    OS << format("%08x %08x %08x CIE",
                 (uint32_t)Offset, (uint32_t)Length, DW_CIE_ID)
       << "\n";
    OS << format("  Version:               %d\n", Version);
    OS << "  Augmentation:          \"" << Augmentation << "\"\n";
    if (Version >= 4) {
      OS << format("  Address size:          %u\n",
                   (uint32_t)AddressSize);
      OS << format("  Segment desc size:     %u\n",
                   (uint32_t)SegmentDescriptorSize);
    }
    OS << format("  Code alignment factor: %u\n",
                 (uint32_t)CodeAlignmentFactor);
    OS << format("  Data alignment factor: %d\n",
                 (int32_t)DataAlignmentFactor);
    OS << format("  Return address column: %d\n",
                 (int32_t)ReturnAddressRegister);
    OS << "\n";
  }
