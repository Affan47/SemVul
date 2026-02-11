hts_findisfile(find_handle find) {
  if (find) {
    if (!hts_findissystem(find)) {
#ifdef _WIN32
      if (!(find->hdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        return 1;
#else
      if (S_ISREG(find->filestat.st_mode))
        return 1;
#endif
    }
  }
  return 0;
}
