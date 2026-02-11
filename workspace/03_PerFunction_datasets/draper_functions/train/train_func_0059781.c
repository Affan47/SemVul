PrepareExternalArrayElements(i::Handle<i::JSObject> object,
                                  void* data,
                                  ExternalArrayType array_type,
                                  int length) {
  i::Isolate* isolate = object->GetIsolate();
  i::Handle<i::ExternalArray> array =
      isolate->factory()->NewExternalArray(length, array_type, data);


  i::Handle<i::HeapObject> elements(object->elements());
  bool cant_reuse_map =
      elements->map()->IsUndefined() ||
      !elements->map()->has_external_array_elements() ||
      elements->map() != isolate->heap()->MapForExternalArrayType(array_type);
  if (cant_reuse_map) {
    i::Handle<i::Map> external_array_map =
        isolate->factory()->GetElementsTransitionMap(
            i::Handle<i::Map>(object->map()),
            GetElementsKindFromExternalArrayType(array_type),
            object->HasFastProperties());
    object->set_map(*external_array_map);
  }
  object->set_elements(*array);
}
