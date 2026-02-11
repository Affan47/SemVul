setName(StringRef Name) {
  if (Name == getName()) return;


  if (SymbolTableEntry) {
    getContext().pImpl->NamedStructTypes.erase(getName());
    SymbolTableEntry = 0;
  }


  if (Name.empty())
    return;


  StringMapEntry<StructType*> *Entry =
    &getContext().pImpl->NamedStructTypes.GetOrCreateValue(Name);


  if (Entry->getValue()) {
    SmallString<64> TempStr(Name);
    TempStr.push_back('.');
    raw_svector_ostream TmpStream(TempStr);

    do {
      TempStr.resize(Name.size()+1);
      TmpStream.resync();
      TmpStream << getContext().pImpl->NamedStructTypesUniqueID++;

      Entry = &getContext().pImpl->
                 NamedStructTypes.GetOrCreateValue(TmpStream.str());
    } while (Entry->getValue());
  }


  Entry->setValue(this);

  SymbolTableEntry = Entry;
}
