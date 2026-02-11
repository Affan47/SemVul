Lookup(String* name, LookupResult* result) {

  for (Object* current = this;
       current != Heap::null_value();
       current = JSObject::cast(current)->GetPrototype()) {
    JSObject::cast(current)->LocalLookup(name, result);
    if (result->IsProperty()) return;
  }
  result->NotFound();
}
