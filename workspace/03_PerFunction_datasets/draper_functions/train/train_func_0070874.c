findModulesDefiningSymbols(std::set<std::string>& symbols,
                                    std::set<Module*>& result,
                                    std::string* error) {
  if (!mapfile || !base) {
    if (error)
      *error = "Empty archive invalid for finding modules defining symbols";
    return false;
  }

  if (symTab.empty()) {


    const char* At  = base + firstFileOffset;
    const char* End = mapfile->getBufferEnd();

    while ( At < End) {

      unsigned offset = At - base - firstFileOffset;


      ArchiveMember* mbr = parseMemberHeader(At, End, error);
      if (!mbr)
        return false;


      if (mbr->isBitcode()) {

        std::vector<std::string> symbols;
        std::string FullMemberName = archPath.str() + "(" +
          mbr->getPath().str() + ")";
        Module* M =
          GetBitcodeSymbols(At, mbr->getSize(), FullMemberName, Context,
                            symbols, error);

        if (M) {

          for (std::vector<std::string>::iterator I = symbols.begin(),
               E=symbols.end(); I != E; ++I ) {
            symTab.insert(std::make_pair(*I, offset));
          }


          modules.insert(std::make_pair(offset, std::make_pair(M, mbr)));
        } else {
          if (error)
            *error = "Can't parse bitcode member: " +
              mbr->getPath().str() + ": " + *error;
          delete mbr;
          return false;
        }
      }


      At += mbr->getSize();
      if ((intptr_t(At) & 1) == 1)
        At++;
    }
  }


  for (std::set<std::string>::iterator I=symbols.begin(),
       E=symbols.end(); I != E;) {

    Module* m = findModuleDefiningSymbol(*I,error);
    if (m) {


      result.insert(m);


      symbols.erase(I++);
    } else {
      ++I;
    }
  }
  return true;
}
