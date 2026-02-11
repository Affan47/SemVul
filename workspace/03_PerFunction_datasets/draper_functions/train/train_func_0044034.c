get_page(char *p, uint32_t bucket, int is_bucket, int is_disk,
                      int is_bitmap) {
  int page, size;
  FileHandle fd = this->fp;
  size = this->BSIZE;

  if ((fd == INVALID_FILE_HANDLE) || !is_disk) {
    PAGE_INIT(p);
    return (0);
  }
  if (is_bucket)
    page = BUCKET_TO_PAGE(bucket);
  else
    page = OADDR_TO_PAGE(bucket);
#ifdef OS_WIN
  LONG off = page << this->BSHIFT;
  SetFilePointer(fd, off, NULL, FILE_BEGIN);
  DWORD rsize;
  if (!ReadFile(fd, p, size, &rsize, NULL)) {
    return -1;
  }
#else
  int rsize = pread(fd, p, size, (off_t)page << this->BSHIFT);
  if (rsize == -1) return (-1);
#endif
  uint16_t *bp = (uint16_t *)p;
  if (!rsize)
    bp[0] = 0;
  else if (rsize != size) {
    return (-1);
  }
  if (!is_bitmap && !bp[0]) {
    PAGE_INIT(p);
  }
  return (0);
}
