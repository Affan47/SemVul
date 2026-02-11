CheckAndClear(int type) {
    alloc_map_lock_.Lock();
    CheckLocked(type);
    if (!IsMMapped()) {
      RAW_CHECK(size1_ == *size2_addr(), "should hold");
    }

    alloc_map_->Insert(data_addr(), type | kDeallocatedTypeBit);
    alloc_map_lock_.Unlock();

    const size_t size = real_size();
    memset(this, kMagicDeletedByte, size);
    return size;
  }
