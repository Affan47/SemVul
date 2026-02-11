GetProbeValue(Isolate* isolate, Code::Flags flags) {

  NumberDictionary* dictionary =
      isolate->heap()->raw_unchecked_non_monomorphic_cache();
  int entry = dictionary->FindEntry(isolate, flags);
  if (entry != -1) return dictionary->ValueAt(entry);
  return isolate->heap()->raw_unchecked_undefined_value();
}
