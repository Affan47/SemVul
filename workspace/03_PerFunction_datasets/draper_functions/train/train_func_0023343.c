readSectionTag(uint32_t Expected) {
  uint32_t Tag;
  if (!GcovBuffer.readInt(Tag))
    return sampleprof_error::truncated;

  if (Tag != Expected)
    return sampleprof_error::malformed;

  if (std::error_code EC = skipNextWord())
    return EC;

  return sampleprof_error::success;
}
