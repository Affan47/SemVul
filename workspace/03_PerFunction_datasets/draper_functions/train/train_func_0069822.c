LookupSymbol(String* string) {
  if (string->IsSymbol()) return string;
  Object* symbol = NULL;
  Object* new_table;
  { MaybeObject* maybe_new_table =
        symbol_table()->LookupString(string, &symbol);
    if (!maybe_new_table->ToObject(&new_table)) return maybe_new_table;
  }


  roots_[kSymbolTableRootIndex] = new_table;
  ASSERT(symbol != NULL);
  return symbol;
}
