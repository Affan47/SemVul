GetEnumPropertyKeys(Handle<JSObject> object,
                                       bool cache_result) {
  int index = 0;
  Isolate* isolate = object->GetIsolate();
  if (object->HasFastProperties()) {
    if (object->map()->instance_descriptors()->HasEnumCache()) {
      isolate->counters()->enum_cache_hits()->Increment();
      DescriptorArray* desc = object->map()->instance_descriptors();
      return Handle<FixedArray>(FixedArray::cast(desc->GetEnumCache()),
                                isolate);
    }
    isolate->counters()->enum_cache_misses()->Increment();
    int num_enum = object->NumberOfEnumProperties();
    Handle<FixedArray> storage = isolate->factory()->NewFixedArray(num_enum);
    Handle<FixedArray> sort_array = isolate->factory()->NewFixedArray(num_enum);
    Handle<DescriptorArray> descs =
        Handle<DescriptorArray>(object->map()->instance_descriptors(), isolate);
    for (int i = 0; i < descs->number_of_descriptors(); i++) {
      if (descs->IsProperty(i) && !descs->IsDontEnum(i)) {
        (*storage)->set(index, descs->GetKey(i));
        PropertyDetails details(descs->GetDetails(i));
        (*sort_array)->set(index, Smi::FromInt(details.index()));
        index++;
      }
    }
    (*storage)->SortPairs(*sort_array, sort_array->length());
    if (cache_result) {
      Handle<FixedArray> bridge_storage =
          isolate->factory()->NewFixedArray(
              DescriptorArray::kEnumCacheBridgeLength);
      DescriptorArray* desc = object->map()->instance_descriptors();
      desc->SetEnumCache(*bridge_storage, *storage);
    }
    ASSERT(storage->length() == index);
    return storage;
  } else {
    int num_enum = object->NumberOfEnumProperties();
    Handle<FixedArray> storage = isolate->factory()->NewFixedArray(num_enum);
    Handle<FixedArray> sort_array = isolate->factory()->NewFixedArray(num_enum);
    object->property_dictionary()->CopyEnumKeysTo(*storage, *sort_array);
    return storage;
  }
}
