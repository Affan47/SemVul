WriteProfile(const char* file_name,
                                    const Bucket& total,
                                    AllocationMap* allocations) {
  RAW_VLOG(1, "Dumping non-live heap profile to %s", file_name);
  RawFD fd = RawOpenForWriting(file_name);
  if (fd != kIllegalRawFD) {
    RawWrite(fd, kProfileHeader, strlen(kProfileHeader));
    char buf[512];
    int len = UnparseBucket(total, buf, 0, sizeof(buf), " heapprofile",
                            NULL);
    RawWrite(fd, buf, len);
    const DumpArgs args(fd, NULL);
    allocations->Iterate<const DumpArgs&>(DumpNonLiveIterator, args);
    RawWrite(fd, kProcSelfMapsHeader, strlen(kProcSelfMapsHeader));
    DumpProcSelfMaps(fd);
    RawClose(fd);
    return true;
  } else {
    RAW_LOG(ERROR, "Failed dumping filtered heap profile to %s", file_name);
    return false;
  }
}
