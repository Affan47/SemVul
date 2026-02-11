PushGTestTrace(const internal::TraceInfo& trace) {
  internal::MutexLock lock(&mutex_);
  impl_->gtest_trace_stack().push_back(trace);
}
