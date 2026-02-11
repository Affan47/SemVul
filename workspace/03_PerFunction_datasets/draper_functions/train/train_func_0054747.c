Allocate(size_t size, int align) {
  MemoryRegion region;
  region.data = 0;
  region.offset = 0;
  if (size > 0) {
    char *buffer = static_cast<char*>(operator new(size + align));
    size_t address = reinterpret_cast<size_t>(buffer);
    region.offset = kArchAlignment - (address % align);
    region.data = buffer + region.offset;
  }
  region.mmap = 0;
  region.size = size;
  return new MappedFile(region);
}
