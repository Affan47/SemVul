ShrinkCache(int locked_size_class, bool force)
    NO_THREAD_SAFETY_ANALYSIS {

  if (cache_size_ == 0) return false;

  if (force == false && used_slots_ == cache_size_) return false;


  LockInverter li(&Static::central_cache()[locked_size_class].lock_, &lock_);
  ASSERT(used_slots_ <= cache_size_);
  ASSERT(0 <= cache_size_);
  if (cache_size_ == 0) return false;
  if (used_slots_ == cache_size_) {
    if (force == false) return false;


    cache_size_--;
    used_slots_--;
    ReleaseListToSpans(tc_slots_[used_slots_].head);
    return true;
  }
  cache_size_--;
  return true;
}
