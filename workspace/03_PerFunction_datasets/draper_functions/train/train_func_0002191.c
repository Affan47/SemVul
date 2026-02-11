Map(istream* s, bool memorymap,
                            const string& source, size_t size) {
  std::streampos spos = s->tellg();
  if (memorymap && spos >= 0 && spos % kArchAlignment == 0) {
    size_t pos = spos;
    int fd = open(source.c_str(), O_RDONLY);
    if (fd != -1) {
      int pagesize = sysconf(_SC_PAGESIZE);
      off_t offset = pos % pagesize;
      off_t upsize = size + offset;
      void *map = mmap(0, upsize, PROT_READ, MAP_SHARED, fd, pos - offset);
      char *data = reinterpret_cast<char*>(map);
      if (close(fd) == 0 && map != MAP_FAILED) {
        MemoryRegion region;
        region.mmap = map;
        region.size = upsize;
        region.data = reinterpret_cast<void*>(data + offset);
        region.offset = offset;
        MappedFile *mmf = new MappedFile(region);
        s->seekg(pos + size, ios::beg);
        if (s) {
          VLOG(1) << "mmap'ed region of " << size << " at offset " << pos
                  << " from " << source << " to addr " << map;
          return mmf;
        }
        delete mmf;
      } else {
        LOG(INFO) << "Mapping of file failed: " << strerror(errno);
      }
    }
  }

  if (memorymap) {
    LOG(WARNING) << "File mapping at offset " << spos << " of file "
                 << source << " could not be honored, reading instead.";
  }
  MappedFile* mf = Allocate(size);
  if (!s->read(reinterpret_cast<char*>(mf->mutable_data()), size)) {
    delete mf;
    return NULL;
  }
  return mf;
}
