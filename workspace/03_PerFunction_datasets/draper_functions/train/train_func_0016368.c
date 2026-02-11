LogFunctionObjects() {
  AssertNoAllocation no_alloc;
  HeapIterator iterator;
  for (HeapObject* obj = iterator.next(); obj != NULL; obj = iterator.next()) {
    if (!obj->IsJSFunction()) continue;
    JSFunction* jsf = JSFunction::cast(obj);
    if (!jsf->is_compiled()) continue;
    LOG(FunctionCreateEvent(jsf));
  }
}
