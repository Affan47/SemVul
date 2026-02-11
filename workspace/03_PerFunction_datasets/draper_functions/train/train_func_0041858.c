ClearNonLiveTransitions(Object* real_prototype) {


  DescriptorArray* d = reinterpret_cast<DescriptorArray*>(
      *RawField(this, Map::kInstanceDescriptorsOffset));
  if (d == Heap::raw_unchecked_empty_descriptor_array()) return;
  Smi* NullDescriptorDetails =
    PropertyDetails(NONE, NULL_DESCRIPTOR).AsSmi();
  FixedArray* contents = reinterpret_cast<FixedArray*>(
      d->get(DescriptorArray::kContentArrayIndex));
  ASSERT(contents->length() >= 2);
  for (int i = 0; i < contents->length(); i += 2) {


    PropertyDetails details(Smi::cast(contents->get(i + 1)));
    if (details.type() == MAP_TRANSITION ||
        details.type() == CONSTANT_TRANSITION) {
      Map* target = reinterpret_cast<Map*>(contents->get(i));
      ASSERT(target->IsHeapObject());
      if (!target->IsMarked()) {
        ASSERT(target->IsMap());
        contents->set_unchecked(i + 1, NullDescriptorDetails);
        contents->set_null_unchecked(i);
        ASSERT(target->prototype() == this ||
               target->prototype() == real_prototype);

        *RawField(target, Map::kPrototypeOffset) = real_prototype;
      }
    }
  }
}
