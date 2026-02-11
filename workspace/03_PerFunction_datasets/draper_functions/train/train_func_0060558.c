AcquireStringInfo(const size_t length)
{
  StringInfo
    *string_info;

  string_info=(StringInfo *) AcquireMagickMemory(sizeof(*string_info));
  if (string_info == (StringInfo *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  (void) ResetMagickMemory(string_info,0,sizeof(*string_info));
  string_info->signature=MagickSignature;
  string_info->length=length;
  if (string_info->length != 0)
    {
      string_info->datum=(unsigned char *) NULL;
      if (~string_info->length >= (MaxTextExtent-1))
        string_info->datum=(unsigned char *) AcquireQuantumMemory(
          string_info->length+MaxTextExtent,sizeof(*string_info->datum));
      if (string_info->datum == (unsigned char *) NULL)
        ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
    }
  return(string_info);
}
