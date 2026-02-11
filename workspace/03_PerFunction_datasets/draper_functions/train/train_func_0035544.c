ExtractElementReferences(JSObject* js_obj,
                                              HeapEntry* entry) {
  if (js_obj->HasFastElements()) {
    FixedArray* elements = FixedArray::cast(js_obj->elements());
    int length = js_obj->IsJSArray() ?
        Smi::cast(JSArray::cast(js_obj)->length())->value() :
        elements->length();
    for (int i = 0; i < length; ++i) {
      if (!elements->get(i)->IsTheHole()) {
        SetElementReference(js_obj, entry, i, elements->get(i));
      }
    }
  } else if (js_obj->HasDictionaryElements()) {
    SeededNumberDictionary* dictionary = js_obj->element_dictionary();
    int length = dictionary->Capacity();
    for (int i = 0; i < length; ++i) {
      Object* k = dictionary->KeyAt(i);
      if (dictionary->IsKey(k)) {
        ASSERT(k->IsNumber());
        uint32_t index = static_cast<uint32_t>(k->Number());
        SetElementReference(js_obj, entry, index, dictionary->ValueAt(i));
      }
    }
  }
}
