Allocate(size_t n) {
    RAW_DCHECK(arena_  &&  heap_checker_lock.IsHeld(), "");
    void* p = LowLevelAlloc::AllocWithArena(n, arena_);
    if (p) alloc_count_ += 1;
    return p;
  }
