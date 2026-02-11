do_malloc_pages(ThreadCache* heap, size_t size) {
  void* result;
  bool report_large;

  Length num_pages = tcmalloc::pages(size);
  size = num_pages << kPageShift;

  if ((FLAGS_tcmalloc_sample_parameter > 0) && heap->SampleAllocation(size)) {
    result = DoSampledAllocation(size);

    SpinLockHolder h(Static::pageheap_lock());
    report_large = should_report_large(num_pages);
  } else {
    SpinLockHolder h(Static::pageheap_lock());
    Span* span = Static::pageheap()->New(num_pages);
    result = (UNLIKELY(span == NULL) ? NULL : SpanToMallocResult(span));
    report_large = should_report_large(num_pages);
  }

  if (report_large) {
    ReportLargeAlloc(num_pages, result);
  }
  return result;
}
