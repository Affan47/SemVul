Lookup(String* name, Code::Flags flags) {
  if (Code::ExtractTypeFromFlags(flags) == NORMAL) {
    return LookupNormalTypeCache(name, flags);
  } else {
    return LookupDefaultCache(name, flags);
  }
}
