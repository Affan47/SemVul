Setup(Address start, size_t size) {
  if (HasBeenSetup()) return false;

  int num_pages = 0;


  int pages_in_chunk = PagesInChunk(start, size);
  if (pages_in_chunk > 0) {
    first_page_ = MemoryAllocator::CommitPages(RoundUp(start, Page::kPageSize),
                                               Page::kPageSize * pages_in_chunk,
                                               this, &num_pages);
  } else {
    int requested_pages =
        Min(MemoryAllocator::kPagesPerChunk,
            static_cast<int>(max_capacity_ / Page::kObjectAreaSize));
    first_page_ =
        MemoryAllocator::AllocatePages(requested_pages, &num_pages, this);
    if (!first_page_->is_valid()) return false;
  }


  ASSERT(first_page_->is_valid());
  ASSERT(num_pages > 0);
  accounting_stats_.ExpandSpace(num_pages * Page::kObjectAreaSize);
  ASSERT(Capacity() <= max_capacity_);


  for (Page* p = first_page_; p->is_valid(); p = p->next_page()) {
    p->SetRegionMarks(Page::kAllRegionsCleanMarks);
    last_page_ = p;
  }


  SetAllocationInfo(&allocation_info_, first_page_);

  page_list_is_chunk_ordered_ = true;

  return true;
}
