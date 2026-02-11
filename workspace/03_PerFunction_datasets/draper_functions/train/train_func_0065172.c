write(const char *ptr, size_t size)
{
  const char *cp = ptr;
  size_t len = size;
  size_t nfree, ncopy;
  size_t written = 0;
  size_t chunk;

  if (!len) return 0;

  while (len) {
    if (chunks) {
      if (offset == CachedFileChunkSize) {
         ++it;
         if (it == (*chunks).end()) return written;
         offset = 0;
      }
      chunk = *it;
    } else {
      offset = cachedFile->length % CachedFileChunkSize;
      chunk = cachedFile->length / CachedFileChunkSize;
    }

    if (chunk >= cachedFile->chunks->size()) {
       cachedFile->chunks->resize(chunk + 1);
    }

    nfree = CachedFileChunkSize - offset;
    ncopy = (len >= nfree) ? nfree : len;
    memcpy(&((*cachedFile->chunks)[chunk].data[offset]), cp, ncopy);
    len -= ncopy;
    cp += ncopy;
    offset += ncopy;
    written += ncopy;

    if (!chunks) {
      cachedFile->length += ncopy;
    }

    if (offset == CachedFileChunkSize) {
       (*cachedFile->chunks)[chunk].state = CachedFile::chunkStateLoaded;
    }
  }

  if ((chunk == (cachedFile->length / CachedFileChunkSize)) &&
      (offset == (cachedFile->length % CachedFileChunkSize))) {
     (*cachedFile->chunks)[chunk].state = CachedFile::chunkStateLoaded;
  }

  return written;
}
