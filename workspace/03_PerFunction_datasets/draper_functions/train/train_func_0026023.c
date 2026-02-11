TearDown() {
  while (first_chunk_ != NULL) {
    LargeObjectChunk* chunk = first_chunk_;
    first_chunk_ = first_chunk_->next();
    chunk->Free(chunk->GetPage()->PageExecutability());
  }
  Setup();
}
