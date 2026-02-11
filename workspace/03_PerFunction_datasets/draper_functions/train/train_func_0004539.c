MemoryStats(int* blocks, size_t* total,
                          int histogram[kMallocHistogramSize]) {
    memset(histogram, 0, kMallocHistogramSize * sizeof(int));
    alloc_map_lock_.Lock();
    stats_blocks_ = 0;
    stats_total_ = 0;
    stats_histogram_ = histogram;
    if (alloc_map_ != NULL) alloc_map_->Iterate(StatsCallback, 0);
    *blocks = stats_blocks_;
    *total = stats_total_;
    alloc_map_lock_.Unlock();
    return true;
  }
