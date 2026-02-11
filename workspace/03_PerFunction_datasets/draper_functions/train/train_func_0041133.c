parseSectionFlags(StringRef flagsStr, bool *UseLastGroup) {
  unsigned flags = 0;

  for (unsigned i = 0; i < flagsStr.size(); i++) {
    switch (flagsStr[i]) {
    case 'a':
      flags |= ELF::SHF_ALLOC;
      break;
    case 'e':
      flags |= ELF::SHF_EXCLUDE;
      break;
    case 'x':
      flags |= ELF::SHF_EXECINSTR;
      break;
    case 'w':
      flags |= ELF::SHF_WRITE;
      break;
    case 'M':
      flags |= ELF::SHF_MERGE;
      break;
    case 'S':
      flags |= ELF::SHF_STRINGS;
      break;
    case 'T':
      flags |= ELF::SHF_TLS;
      break;
    case 'c':
      flags |= ELF::XCORE_SHF_CP_SECTION;
      break;
    case 'd':
      flags |= ELF::XCORE_SHF_DP_SECTION;
      break;
    case 'G':
      flags |= ELF::SHF_GROUP;
      break;
    case '?':
      *UseLastGroup = true;
      break;
    default:
      return -1U;
    }
  }

  return flags;
}
