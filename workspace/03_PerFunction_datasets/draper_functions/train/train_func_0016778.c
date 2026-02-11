EnsurePropertyCell(String* name) {
  ASSERT(!HasFastProperties());
  int entry = property_dictionary()->FindEntry(name);
  if (entry == StringDictionary::kNotFound) {
    Heap* heap = GetHeap();
    Object* cell;
    { MaybeObject* maybe_cell =
          heap->AllocateJSGlobalPropertyCell(heap->the_hole_value());
      if (!maybe_cell->ToObject(&cell)) return maybe_cell;
    }
    PropertyDetails details(NONE, NORMAL);
    details = details.AsDeleted();
    Object* dictionary;
    { MaybeObject* maybe_dictionary =
          property_dictionary()->Add(name, cell, details);
      if (!maybe_dictionary->ToObject(&dictionary)) return maybe_dictionary;
    }
    set_properties(StringDictionary::cast(dictionary));
    return cell;
  } else {
    Object* value = property_dictionary()->ValueAt(entry);
    ASSERT(value->IsJSGlobalPropertyCell());
    return value;
  }
}
