SlowReverseLookup(Object* value) {
  if (HasFastProperties()) {
    DescriptorArray* descs = map()->instance_descriptors();
    for (int i = 0; i < descs->number_of_descriptors(); i++) {
      if (descs->GetType(i) == FIELD) {
        if (FastPropertyAt(descs->GetFieldIndex(i)) == value) {
          return descs->GetKey(i);
        }
      } else if (descs->GetType(i) == CONSTANT_FUNCTION) {
        if (descs->GetConstantFunction(i) == value) {
          return descs->GetKey(i);
        }
      }
    }
    return GetHeap()->undefined_value();
  } else {
    return property_dictionary()->SlowReverseLookup(value);
  }
}
