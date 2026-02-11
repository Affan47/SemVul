NativesSourceLookup(int index) {
  ASSERT(0 <= index && index < Natives::GetBuiltinsCount());
  Isolate* isolate = Isolate::Current();
  Factory* factory = isolate->factory();
  Heap* heap = isolate->heap();
  if (heap->natives_source_cache()->get(index)->IsUndefined()) {
    if (!Snapshot::IsEnabled() || FLAG_new_snapshot) {

      Vector<const char> source = Natives::GetRawScriptSource(index);
      NativesExternalStringResource* resource =
          new NativesExternalStringResource(this,
                                            source.start(),
                                            source.length());
      Handle<String> source_code =
          factory->NewExternalStringFromAscii(resource);
      heap->natives_source_cache()->set(index, *source_code);
    } else {

      Handle<String> source_code =
        factory->NewStringFromAscii(Natives::GetRawScriptSource(index));
      heap->natives_source_cache()->set(index, *source_code);
    }
  }
  Handle<Object> cached_source(heap->natives_source_cache()->get(index));
  return Handle<String>::cast(cached_source);
}
