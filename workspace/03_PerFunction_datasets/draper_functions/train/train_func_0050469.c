DefineGetterSetter(String* name,
                                          PropertyAttributes attributes) {


  AssertNoContextChange ncc;


  name->TryFlatten();

  if (!CanSetCallback(name)) {
    return Heap::undefined_value();
  }

  uint32_t index = 0;
  bool is_element = name->AsArrayIndex(&index);

  if (is_element) {
    switch (GetElementsKind()) {
      case FAST_ELEMENTS:
        break;
      case PIXEL_ELEMENTS:
      case EXTERNAL_BYTE_ELEMENTS:
      case EXTERNAL_UNSIGNED_BYTE_ELEMENTS:
      case EXTERNAL_SHORT_ELEMENTS:
      case EXTERNAL_UNSIGNED_SHORT_ELEMENTS:
      case EXTERNAL_INT_ELEMENTS:
      case EXTERNAL_UNSIGNED_INT_ELEMENTS:
      case EXTERNAL_FLOAT_ELEMENTS:


        return Heap::undefined_value();
      case DICTIONARY_ELEMENTS: {

        NumberDictionary* dictionary = element_dictionary();
        int entry = dictionary->FindEntry(index);
        if (entry != NumberDictionary::kNotFound) {
          Object* result = dictionary->ValueAt(entry);
          PropertyDetails details = dictionary->DetailsAt(entry);
          if (details.IsReadOnly()) return Heap::undefined_value();
          if (details.type() == CALLBACKS) {
            if (result->IsFixedArray()) {
              return result;
            }

          }
        }
        break;
      }
      default:
        UNREACHABLE();
        break;
    }
  } else {

    LookupResult result;
    LocalLookup(name, &result);
    if (result.IsProperty()) {
      if (result.IsReadOnly()) return Heap::undefined_value();
      if (result.type() == CALLBACKS) {
        Object* obj = result.GetCallbackObject();

        if (obj->IsFixedArray()) {

          return SetPropertyCallback(name, obj, attributes);
        }
      }
    }
  }


  Object* structure;
  { MaybeObject* maybe_structure = Heap::AllocateFixedArray(2, TENURED);
    if (!maybe_structure->ToObject(&structure)) return maybe_structure;
  }

  if (is_element) {
    return SetElementCallback(index, structure, attributes);
  } else {
    return SetPropertyCallback(name, structure, attributes);
  }
}
