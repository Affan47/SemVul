Free(Executability executable) {
  size_t guard_size = (executable == EXECUTABLE) ? Page::kPageSize : 0;
  ObjectSpace space =
      (executable == EXECUTABLE) ? kObjectSpaceCodeSpace : kObjectSpaceLoSpace;

  Address my_address = address();
  size_t my_size = size();
  Isolate* isolate = GetPage()->heap_->isolate();
  MemoryAllocator* a = isolate->memory_allocator();
  a->FreeRawMemory(my_address - guard_size, my_size + guard_size, executable);
  a->PerformAllocationCallback(space, kAllocationActionFree, my_size);
  LOG(isolate, DeleteEvent("LargeObjectChunk", my_address));
}
