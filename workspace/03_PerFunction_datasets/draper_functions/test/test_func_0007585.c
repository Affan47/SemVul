LookupCallbackSetterInPrototypes(String* name,
                                                LookupResult* result) {
  Heap* heap = GetHeap();
  for (Object* pt = GetPrototype();
       pt != heap->null_value();
       pt = pt->GetPrototype()) {
    JSObject::cast(pt)->LocalLookupRealNamedProperty(name, result);
    if (result->IsProperty()) {
      if (result->type() == CALLBACKS && !result->IsReadOnly()) return;

      break;
    }
  }
  result->NotFound();
}
