isPrecededByMatchingHi(const MCAssembler &Asm, uint32_t Index,
                       std::vector<MipsRelocationEntry> &MipsRelocs) {
  return Index < MipsRelocs.size() - 1 &&
         areMatchingHiAndLo(Asm, MipsRelocs[Index + 1].R, MipsRelocs[Index].R);
}
