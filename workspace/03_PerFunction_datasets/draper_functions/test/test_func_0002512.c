lnx_mem_proc() {
  KeyValueFileParser meminfo("/proc/meminfo");

  if(!meminfo.FileReadable()) {
    DBG("could not open proc memory filesystem");
    return 0;
  }

  KeyValPair *mem_total = meminfo.GetData("MemTotal");
  if(mem_total == NULL) {
    DBG("proc mem fs did not have a `MemTotal' entry.");
    return 0;
  }
  std::istringstream mem_strm(mem_total->strValue);
  uint64_t mem;
  mem_strm >> mem;
  return mem * 1024;
}
