Initialize(bool create_heap_objects) {
  ASSERT(IsPowerOf2(kPrimaryTableSize));
  ASSERT(IsPowerOf2(kSecondaryTableSize));
  if (create_heap_objects) {
    HandleScope scope;
    Clear();
  }
}
