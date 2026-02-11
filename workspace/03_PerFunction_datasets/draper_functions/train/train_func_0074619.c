MCAllocateFromNewSpace(HeapObject* object,
                                           int object_size) {
  MaybeObject* forwarded;
  if (object_size > Heap::MaxObjectSizeInPagedSpace()) {
    forwarded = Failure::Exception();
  } else {
    OldSpace* target_space = Heap::TargetSpace(object);
    ASSERT(target_space == Heap::old_pointer_space() ||
           target_space == Heap::old_data_space());
    forwarded = target_space->MCAllocateRaw(object_size);
  }
  Object* result;
  if (!forwarded->ToObject(&result)) {
    result = Heap::new_space()->MCAllocateRaw(object_size)->ToObjectUnchecked();
  }
  return result;
}
