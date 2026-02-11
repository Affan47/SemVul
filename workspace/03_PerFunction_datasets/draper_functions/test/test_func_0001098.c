Init(const unsigned char *Buckets,
                                const unsigned char *const Payload,
                                const unsigned char *const Base,
                                IndexedInstrProf::HashT HashType,
                                uint64_t Version) {
  FormatVersion = Version;
  Index.reset(IndexType::Create(Buckets, Payload, Base,
                                InstrProfLookupTrait(HashType, Version)));

  std::vector<std::pair<uint64_t, const char *>> HashKeys;
  for (auto Key : Index->keys()) {
    const char *KeyTableRef = StringTable.insertString(Key);
    HashKeys.push_back(std::make_pair(ComputeHash(HashType, Key), KeyTableRef));
  }
  std::sort(HashKeys.begin(), HashKeys.end(), less_first());
  HashKeys.erase(std::unique(HashKeys.begin(), HashKeys.end()), HashKeys.end());

  Index->getInfoObj().setHashKeys(std::move(HashKeys));
  RecordIterator = Index->data_begin();
}
