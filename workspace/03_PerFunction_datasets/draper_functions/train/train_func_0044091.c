SetNumericProperty(const char* name, size_t value) {
    ASSERT(name != NULL);

    if (strcmp(name, "tcmalloc.max_total_thread_cache_bytes") == 0) {
      SpinLockHolder l(Static::pageheap_lock());
      ThreadCache::set_overall_thread_cache_size(value);
      return true;
    }

    if (strcmp(name, "tcmalloc.aggressive_memory_decommit") == 0) {
      Static::pageheap()->SetAggressiveDecommit(value != 0);
      return true;
    }

    return false;
  }
