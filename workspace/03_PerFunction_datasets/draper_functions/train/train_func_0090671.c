set_next(Address next) {
  ASSERT(IsFreeListNode(this));
  if (map() == Heap::raw_unchecked_byte_array_map()) {
    ASSERT(Size() >= kNextOffset + kPointerSize);
    Memory::Address_at(address() + kNextOffset) = next;
  } else {
    Memory::Address_at(address() + kPointerSize) = next;
  }
}
