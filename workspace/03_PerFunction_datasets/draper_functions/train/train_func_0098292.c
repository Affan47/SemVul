UpdatePointerToNewGen(HeapObject** p) {
  if (!(*p)->IsHeapObject()) return;

  Address old_addr = (*p)->address();
  ASSERT(HEAP->InFromSpace(*p));

  Address new_addr = Memory::Address_at(old_addr);

  if (new_addr == NULL) {


    *p = NULL;
  } else {
    *p = HeapObject::FromAddress(new_addr);
  }
}
