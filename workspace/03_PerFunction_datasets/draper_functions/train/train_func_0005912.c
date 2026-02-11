open(const char* pathname, int flags)
{
#ifdef WIN32
  HANDLE hFile = CreateFile(pathname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
  if (hFile != INVALID_HANDLE_VALUE) {
    ULARGE_INTEGER FileSize;
    FileSize.LowPart = GetFileSize(hFile, &FileSize.HighPart);
    CloseHandle(hFile);
    if ((FileSize.LowPart != INVALID_FILE_SIZE) || (GetLastError() == NO_ERROR)) {
      hd_size = FileSize.QuadPart;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
#endif

  fd = ::open(pathname, flags
#ifdef O_BINARY
              | O_BINARY
#endif
              );

  if (fd < 0) {
    return fd;
  }

#ifndef WIN32

  struct stat stat_buf;
  int ret = fstat(fd, &stat_buf);
  if (ret) {
    BX_PANIC(("fstat() returns error!"));
  }
  hd_size = (Bit64u)stat_buf.st_size;
#endif
  if ((hd_size % 512) != 0) {
    BX_PANIC(("size of disk image must be multiple of 512 bytes"));
  }

  return fd;
}
