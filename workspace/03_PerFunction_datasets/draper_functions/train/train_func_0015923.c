getFileOrSTDIN(const char *Filename,
                                        OwningPtr<MemoryBuffer> &result,
                                        int64_t FileSize) {
  if (strcmp(Filename, "-") == 0)
    return getSTDIN(result);
  return getFile(Filename, result, FileSize);
}
