readNameTable() {
  if (std::error_code EC = readSectionTag(GCOVTagAFDOFileNames))
    return EC;

  uint32_t Size;
  if (!GcovBuffer.readInt(Size))
    return sampleprof_error::truncated;

  for (uint32_t I = 0; I < Size; ++I) {
    StringRef Str;
    if (!GcovBuffer.readString(Str))
      return sampleprof_error::truncated;
    Names.push_back(Str);
  }

  return sampleprof_error::success;
}
