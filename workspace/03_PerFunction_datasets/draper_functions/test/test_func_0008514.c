CreateScriptCache() {
  Heap* heap = isolate_->heap();
  HandleScope scope(isolate_);


  heap->CollectAllGarbage(false);
  heap->CollectAllGarbage(false);

  ASSERT(script_cache_ == NULL);
  script_cache_ = new ScriptCache();


  int count = 0;
  HeapIterator iterator;
  for (HeapObject* obj = iterator.next(); obj != NULL; obj = iterator.next()) {
    if (obj->IsScript() && Script::cast(obj)->HasValidSource()) {
      script_cache_->Add(Handle<Script>(Script::cast(obj)));
      count++;
    }
  }
}
