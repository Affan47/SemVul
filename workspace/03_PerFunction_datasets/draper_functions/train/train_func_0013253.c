ReleaseAtLeastNPages(Length num_pages) {
  Length released_pages = 0;


  while (released_pages < num_pages && stats_.free_bytes > 0) {
    for (int i = 0; i < kMaxPages+1 && released_pages < num_pages;
         i++, release_index_++) {
      if (release_index_ > kMaxPages) release_index_ = 0;
      SpanList* slist = (release_index_ == kMaxPages) ?
          &large_ : &free_[release_index_];
      if (!DLL_IsEmpty(&slist->normal)) {
        Length released_len = ReleaseLastNormalSpan(slist);

        if (released_len == 0) return released_pages;
        released_pages += released_len;
      }
    }
  }
  return released_pages;
}
