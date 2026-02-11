emitTypeInfos(unsigned TTypeEncoding) {
  const std::vector<const GlobalValue *> &TypeInfos = MMI->getTypeInfos();
  const std::vector<unsigned> &FilterIds = MMI->getFilterIds();

  bool VerboseAsm = Asm->OutStreamer->isVerboseAsm();

  int Entry = 0;

  if (VerboseAsm && !TypeInfos.empty()) {
    Asm->OutStreamer->AddComment(">> Catch TypeInfos <<");
    Asm->OutStreamer->AddBlankLine();
    Entry = TypeInfos.size();
  }

  for (const GlobalValue *GV : make_range(TypeInfos.rbegin(),
                                          TypeInfos.rend())) {
    if (VerboseAsm)
      Asm->OutStreamer->AddComment("TypeInfo " + Twine(Entry--));
    Asm->EmitTTypeReference(GV, TTypeEncoding);
  }


  if (VerboseAsm && !FilterIds.empty()) {
    Asm->OutStreamer->AddComment(">> Filter TypeInfos <<");
    Asm->OutStreamer->AddBlankLine();
    Entry = 0;
  }
  for (std::vector<unsigned>::const_iterator
         I = FilterIds.begin(), E = FilterIds.end(); I < E; ++I) {
    unsigned TypeID = *I;
    if (VerboseAsm) {
      --Entry;
      if (isFilterEHSelector(TypeID))
        Asm->OutStreamer->AddComment("FilterInfo " + Twine(Entry));
    }

    Asm->EmitULEB128(TypeID);
  }
}
