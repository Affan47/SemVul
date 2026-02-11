LookupSymbolIfExists(String* string, String** symbol) {
  if (string->IsSymbol()) {
    *symbol = string;
    return true;
  }
  return symbol_table()->LookupSymbolIfExists(string, symbol);
}
