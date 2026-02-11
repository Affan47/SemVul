SetPropertyCallback(String* name,
                                           Object* structure,
                                           PropertyAttributes attributes) {
  PropertyDetails details = PropertyDetails(attributes, CALLBACKS);

  bool convert_back_to_fast = HasFastProperties() &&
      (map()->instance_descriptors()->number_of_descriptors()
          < DescriptorArray::kMaxNumberOfDescriptors);


  Object* ok;
  { MaybeObject* maybe_ok = NormalizeProperties(CLEAR_INOBJECT_PROPERTIES, 0);
    if (!maybe_ok->ToObject(&ok)) return maybe_ok;
  }


  if (IsGlobalObject()) {
    Object* new_map;
    { MaybeObject* maybe_new_map = map()->CopyDropDescriptors();
      if (!maybe_new_map->ToObject(&new_map)) return maybe_new_map;
    }
    set_map(Map::cast(new_map));


    Deoptimizer::DeoptimizeGlobalObject(this);
  }


  Object* result;
  { MaybeObject* maybe_result = SetNormalizedProperty(name, structure, details);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }

  if (convert_back_to_fast) {
    { MaybeObject* maybe_ok = TransformToFastProperties(0);
      if (!maybe_ok->ToObject(&ok)) return maybe_ok;
    }
  }
  return result;
}
