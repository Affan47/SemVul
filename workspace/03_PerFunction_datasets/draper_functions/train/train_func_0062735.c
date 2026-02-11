ContextSlotIndex(String* name, Variable::Mode* mode) {
  ASSERT(name->IsSymbol());
  Isolate* isolate = GetIsolate();
  int result = isolate->context_slot_cache()->Lookup(this, name, mode);
  if (result != ContextSlotCache::kNotFound) return result;
  if (length() > 0) {

    Object** p0 = ContextEntriesAddr();
    int number_of_context_slots;
    p0 = ReadInt(p0, &number_of_context_slots);
    Object** p = p0;
    Object** end = p0 + number_of_context_slots * 2;
    while (p != end) {
      if (*p == name) {
        ASSERT(((p - p0) & 1) == 0);
        int v;
        ReadInt(p + 1, &v);
        Variable::Mode mode_value = static_cast<Variable::Mode>(v);
        if (mode != NULL) *mode = mode_value;
        result = static_cast<int>((p - p0) >> 1) + Context::MIN_CONTEXT_SLOTS;
        isolate->context_slot_cache()->Update(this, name, mode_value, result);
        return result;
      }
      p += 2;
    }
  }
  isolate->context_slot_cache()->Update(this, name, Variable::INTERNAL, -1);
  return -1;
}
