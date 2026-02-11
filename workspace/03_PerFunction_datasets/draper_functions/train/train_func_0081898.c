computeRelocation(unsigned SymOffset,
                                             unsigned RelOffset,
                                             unsigned RelTy) const {

  if (RelTy == ELF::R_X86_64_PC32 || RelTy == ELF::R_386_PC32)
    return SymOffset - (RelOffset + 4);
  else
    assert(0 && "computeRelocation unknown for this relocation type");

  return 0;
}
