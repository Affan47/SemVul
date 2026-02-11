WriteResource(const std::string& id, size_t index) {
  Entry* entry = GetOrCreateEntry(id, false);
  if (LS_LOCKED != entry->lock_state)
    return NULL;

  size_t previous_size = 0;
  std::string filename(IdToFilename(id, index));
  FileStream::GetSize(filename, &previous_size);
  ASSERT(previous_size <= entry->size);
  if (previous_size > entry->size) {
    previous_size = entry->size;
  }

  scoped_ptr<FileStream> file(new FileStream);
  if (!file->Open(filename, "wb", NULL)) {
    LOG_F(LS_ERROR) << "Couldn't create cache file";
    return NULL;
  }

  entry->streams = stdmax(entry->streams, index + 1);
  entry->size -= previous_size;
  total_size_ -= previous_size;

  entry->accessors += 1;
  total_accessors_ += 1;
  return new DiskCacheAdapter(this, id, index, file.release());
}
