emitDebugStr() {

  if (StringPool.empty()) return;


  Asm->OutStreamer.SwitchSection(
                                Asm->getObjFileLowering().getDwarfStrSection());


  SmallVector<std::pair<unsigned,
      StringMapEntry<std::pair<MCSymbol*, unsigned> >*>, 64> Entries;

  for (StringMap<std::pair<MCSymbol*, unsigned> >::iterator
       I = StringPool.begin(), E = StringPool.end(); I != E; ++I)
    Entries.push_back(std::make_pair(I->second.second, &*I));

  array_pod_sort(Entries.begin(), Entries.end());

  for (unsigned i = 0, e = Entries.size(); i != e; ++i) {

    Asm->OutStreamer.EmitLabel(Entries[i].second->getValue().first);


    Asm->OutStreamer.EmitBytes(Entries[i].second->getKey(), 0);
  }
}
