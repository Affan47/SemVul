next(Heap* heap) {
  ASSERT(IsFreeListNode(this));
  if (map() == heap->raw_unchecked_byte_array_map()) {
    ASSERT(Size() >= kNextOffset + kPointerSize);
    return Memory::Address_at(address() + kNextOffset);
  } else {
    return Memory::Address_at(address() + kPointerSize);
  }
}
