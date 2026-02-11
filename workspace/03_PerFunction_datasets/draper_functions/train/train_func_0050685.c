Put(FixedArray* array, Map* value) {
  SymbolsKey key(array);
  Object* obj;
  { MaybeObject* maybe_obj = EnsureCapacity(1, &key);
    if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  }

  MapCache* cache = reinterpret_cast<MapCache*>(obj);
  int entry = cache->FindInsertionEntry(key.Hash());
  cache->set(EntryToIndex(entry), array);
  cache->set(EntryToIndex(entry) + 1, value);
  cache->ElementAdded();
  return cache;
}
