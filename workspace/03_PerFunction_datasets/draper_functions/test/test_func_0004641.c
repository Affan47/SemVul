AllocateRawMemory(const size_t requested,
                                         size_t* allocated,
                                         Executability executable) {
  if (size_ + static_cast<size_t>(requested) > static_cast<size_t>(capacity_)) {
    return NULL;
  }

  void* mem;
  if (executable == EXECUTABLE) {

    if (size_executable_ + requested >
        static_cast<size_t>(capacity_executable_)) {
      LOG(isolate_,
          StringEvent("MemoryAllocator::AllocateRawMemory",
                      "V8 Executable Allocation capacity exceeded"));
      return NULL;
    }


    if (isolate_->code_range()->exists()) {
      mem = isolate_->code_range()->AllocateRawMemory(requested, allocated);
    } else {
      mem = OS::Allocate(requested, allocated, true);
    }

    size_executable_ += static_cast<int>(*allocated);
  } else {
    mem = OS::Allocate(requested, allocated, false);
  }
  int alloced = static_cast<int>(*allocated);
  size_ += alloced;

#ifdef DEBUG
  ZapBlock(reinterpret_cast<Address>(mem), alloced);
#endif
  isolate_->counters()->memory_allocated()->Increment(alloced);
  return mem;
}
