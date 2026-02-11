BytesLeaked() const {
  SpinLockHolder l(lock_);
  if (!has_checked_) {
    RAW_LOG(FATAL, "*NoLeaks|SameHeap must execute before this call");
  }
  return inuse_bytes_increase_;
}
