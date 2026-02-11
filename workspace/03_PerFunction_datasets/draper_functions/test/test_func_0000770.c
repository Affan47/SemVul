SetProgressTotal(int iterations_count) {
  if (control_ == NULL) return;
  progress_total_ = v8_heap_explorer_.EstimateObjectsCount() * iterations_count;
  progress_counter_ = 0;
}
