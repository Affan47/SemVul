TBufferNewPage(VP8TBuffer* const b) {
  VP8Tokens* page = NULL;
  if (!b->error_) {
    const size_t size = sizeof(*page) + b->page_size_ * sizeof(token_t);
    page = (VP8Tokens*)WebPSafeMalloc(1ULL, size);
  }
  if (page == NULL) {
    b->error_ = 1;
    return 0;
  }
  page->next_ = NULL;

  *b->last_page_ = page;
  b->last_page_ = &page->next_;
  b->left_ = b->page_size_;
  b->tokens_ = (token_t*)TOKEN_DATA(page);
  return 1;
}
