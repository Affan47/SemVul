FindSymbol(const string& key) const {
  const Symbol* result = FindOrNull(symbols_by_name_, key.c_str());
  if (result == NULL) {
    return kNullSymbol;
  } else {
    return *result;
  }
}
