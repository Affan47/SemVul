print(raw_ostream &O) {

  Header.print(O);
  HeaderData.print(O);

  O << "Entries: \n";
  for (StringMap<DataArray>::const_iterator EI = Entries.begin(),
                                            EE = Entries.end();
       EI != EE; ++EI) {
    O << "Name: " << EI->getKeyData() << "\n";
    for (HashDataContents *HD : EI->second.Values)
      HD->print(O);
  }

  O << "Buckets and Hashes: \n";
  for (size_t i = 0, e = Buckets.size(); i < e; ++i)
    for (HashList::const_iterator HI = Buckets[i].begin(),
                                  HE = Buckets[i].end();
         HI != HE; ++HI)
      (*HI)->print(O);

  O << "Data: \n";
  for (std::vector<HashData *>::const_iterator DI = Data.begin(),
                                               DE = Data.end();
       DI != DE; ++DI)
    (*DI)->print(O);
}
