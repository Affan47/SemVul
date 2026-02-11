GetLocalPropertyNames(FixedArray* storage, int index) {
  ASSERT(storage->length() >= (NumberOfLocalProperties(NONE) - index));
  if (HasFastProperties()) {
    DescriptorArray* descs = map()->instance_descriptors();
    for (int i = 0; i < descs->number_of_descriptors(); i++) {
      if (descs->IsProperty(i)) storage->set(index++, descs->GetKey(i));
    }
    ASSERT(storage->length() >= index);
  } else {
    property_dictionary()->CopyKeysTo(storage,
                                      index,
                                      StringDictionary::UNSORTED);
  }
}
