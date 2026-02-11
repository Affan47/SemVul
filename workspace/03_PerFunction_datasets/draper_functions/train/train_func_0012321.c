relocate(void *Function, MachineRelocation *MR,
                          unsigned NumRelocs, unsigned char* GOTBase) {
  for (unsigned i = 0; i != NumRelocs; ++i, ++MR) {
    void *RelocPos = (char*)Function + MR->getMachineCodeOffset();
    intptr_t ResultPtr = (intptr_t)MR->getResultPointer();
    switch ((X86::RelocationType)MR->getRelocationType()) {
    case X86::reloc_pcrel_word: {


      ResultPtr = ResultPtr -(intptr_t)RelocPos - 4 - MR->getConstantVal();
      *((unsigned*)RelocPos) += (unsigned)ResultPtr;
      break;
    }
    case X86::reloc_picrel_word: {


      ResultPtr = ResultPtr - ((intptr_t)Function + MR->getConstantVal());
      *((unsigned*)RelocPos) += (unsigned)ResultPtr;
      break;
    }
    case X86::reloc_absolute_word:
    case X86::reloc_absolute_word_sext:


      *((unsigned*)RelocPos) += (unsigned)ResultPtr;
      break;
    case X86::reloc_absolute_dword:
      *((intptr_t*)RelocPos) += ResultPtr;
      break;
    }
  }
}
