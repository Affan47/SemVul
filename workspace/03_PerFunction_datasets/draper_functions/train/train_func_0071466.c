relocate(void *Function, MachineRelocation *MR,
    unsigned NumRelocs, unsigned char* GOTBase) {
  for (unsigned i = 0; i != NumRelocs; ++i, ++MR) {

    void *RelocPos = (char*) Function + MR->getMachineCodeOffset();
    intptr_t ResultPtr = (intptr_t) MR->getResultPointer();

    switch ((Mips::RelocationType) MR->getRelocationType()) {
    case Mips::reloc_mips_branch:
      ResultPtr = (((ResultPtr - (intptr_t) RelocPos) - 4) >> 2) & 0xffff;
      *((unsigned*) RelocPos) |= (unsigned) ResultPtr;
      break;

    case Mips::reloc_mips_26:
      ResultPtr = (ResultPtr & 0x0fffffff) >> 2;
      *((unsigned*) RelocPos) |= (unsigned) ResultPtr;
      break;

    case Mips::reloc_mips_hi:
      ResultPtr = ResultPtr >> 16;
      if ((((intptr_t) (MR->getResultPointer()) & 0xffff) >> 15) == 1) {
        ResultPtr += 1;
      }
      *((unsigned*) RelocPos) |= (unsigned) ResultPtr;
      break;

    case Mips::reloc_mips_lo:
      ResultPtr = ResultPtr & 0xffff;
      *((unsigned*) RelocPos) |= (unsigned) ResultPtr;
      break;

    default:
      llvm_unreachable("ERROR: Unknown Mips relocation.");
    }
  }
}
