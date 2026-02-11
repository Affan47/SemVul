AddOrDisposeString(char* str, uint32_t hash) {
  HashMap::Entry* cache_entry = names_.Lookup(str, hash, true);
  if (cache_entry->value == NULL) {

    cache_entry->value = str;
  } else {
    DeleteArray(str);
  }
  return reinterpret_cast<const char*>(cache_entry->value);
}
