PartialSnapshotCacheIndex(HeapObject* heap_object) {
  for (int i = 0; i < partial_snapshot_cache_length_; i++) {
    Object* entry = partial_snapshot_cache_[i];
    if (entry == heap_object) return i;
  }


  int length = partial_snapshot_cache_length_;
  CHECK(length < kPartialSnapshotCacheCapacity);
  partial_snapshot_cache_[length] = heap_object;
  startup_serializer_->VisitPointer(&partial_snapshot_cache_[length]);


  ASSERT(length == partial_snapshot_cache_length_);
  return partial_snapshot_cache_length_++;
}
