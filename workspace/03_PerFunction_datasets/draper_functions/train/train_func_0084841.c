find_unit_by_pattern(const char *pattern) {
  UnitLib_Entry *entry;
  iterate_units_begin();
  while ((entry = iterate_units_next())) {
    if (strcasestr(entry->name, pattern)) return entry;
  }
  return 0;
}
