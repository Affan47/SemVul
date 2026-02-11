FindObject(Address a) {
  for (LargeObjectChunk* chunk = first_chunk_;
       chunk != NULL;
       chunk = chunk->next()) {
    Address chunk_address = chunk->address();
    if (chunk_address <= a && a < chunk_address + chunk->size()) {
      return chunk->GetObject();
    }
  }
  return Failure::Exception();
}
