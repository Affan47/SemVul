readFunctionProfiles() {
  if (std::error_code EC = readSectionTag(GCOVTagAFDOFunction))
    return EC;

  uint32_t NumFunctions;
  if (!GcovBuffer.readInt(NumFunctions))
    return sampleprof_error::truncated;

  InlineCallStack Stack;
  for (uint32_t I = 0; I < NumFunctions; ++I)
    if (std::error_code EC = readOneFunctionProfile(Stack, true, 0))
      return EC;

  return sampleprof_error::success;
}
