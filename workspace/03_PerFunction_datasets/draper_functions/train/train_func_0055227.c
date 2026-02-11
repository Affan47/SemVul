End() const {
  if (FLAG_time_hydrogen) {
    int64_t end = OS::Ticks();
    unsigned size = Zone::allocation_size_ - start_allocation_size_;
    HStatistics::Instance()->SaveTiming(name_, end - start_, size);
  }

  if (FLAG_trace_hydrogen) {
    if (graph_ != NULL) HTracer::Instance()->TraceHydrogen(name_, graph_);
    if (chunk_ != NULL) HTracer::Instance()->TraceLithium(name_, chunk_);
    if (allocator_ != NULL) {
      HTracer::Instance()->TraceLiveRanges(name_, allocator_);
    }
  }

#ifdef DEBUG
  if (graph_ != NULL) graph_->Verify();
  if (allocator_ != NULL) allocator_->Verify();
#endif
}
