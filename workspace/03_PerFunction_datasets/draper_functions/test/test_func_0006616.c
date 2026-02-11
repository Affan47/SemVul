GetTable(int generation) {
  ASSERT(generation < generations_);
  Handle<CompilationCacheTable> result;
  if (tables_[generation]->IsUndefined()) {
    result = AllocateTable(kInitialCacheSize);
    tables_[generation] = *result;
  } else {
    CompilationCacheTable* table =
        CompilationCacheTable::cast(tables_[generation]);
    result = Handle<CompilationCacheTable>(table);
  }
  return result;
}
