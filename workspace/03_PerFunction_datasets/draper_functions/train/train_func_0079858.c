checkOffset(MemoryBufferRef M, uintptr_t Addr,
                                   const uint64_t Size) {
  if (Addr + Size < Addr || Addr + Size < Size ||
      Addr + Size > uintptr_t(M.getBufferEnd()) ||
      Addr < uintptr_t(M.getBufferStart())) {
    return std::make_error_code(std::errc::bad_address);
  }
  return std::error_code();
}
