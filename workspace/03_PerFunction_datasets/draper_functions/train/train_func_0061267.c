AutoDetectSubtargetFeatures() {
  unsigned EAX = 0, EBX = 0, ECX = 0, EDX = 0;
  union {
    unsigned u[3];
    char     c[12];
  } text;

  if (GetCpuIDAndInfo(0, &EAX, text.u+0, text.u+2, text.u+1))
    return;

  GetCpuIDAndInfo(0x1, &EAX, &EBX, &ECX, &EDX);

  if ((EDX >> 15) & 1) HasCMov = true;
  if ((EDX >> 23) & 1) X86SSELevel = MMX;
  if ((EDX >> 25) & 1) X86SSELevel = SSE1;
  if ((EDX >> 26) & 1) X86SSELevel = SSE2;
  if (ECX & 0x1)       X86SSELevel = SSE3;
  if ((ECX >> 9)  & 1) X86SSELevel = SSSE3;
  if ((ECX >> 19) & 1) X86SSELevel = SSE41;
  if ((ECX >> 20) & 1) X86SSELevel = SSE42;

  bool IsIntel = memcmp(text.c, "GenuineIntel", 12) == 0;
  bool IsAMD   = !IsIntel && memcmp(text.c, "AuthenticAMD", 12) == 0;

  HasCLMUL = IsIntel && ((ECX >> 1) & 0x1);
  HasFMA3  = IsIntel && ((ECX >> 12) & 0x1);
  HasAVX   = ((ECX >> 28) & 0x1);
  HasAES   = IsIntel && ((ECX >> 25) & 0x1);

  if (IsIntel || IsAMD) {

    unsigned Family = 0;
    unsigned Model  = 0;
    DetectFamilyModel(EAX, Family, Model);
    IsBTMemSlow = IsAMD || (Family == 6 && Model >= 13);

    if (Family == 15 && Model == 26)
      IsUAMemFast = true;

    GetCpuIDAndInfo(0x80000001, &EAX, &EBX, &ECX, &EDX);
    HasX86_64 = (EDX >> 29) & 0x1;
    HasSSE4A = IsAMD && ((ECX >> 6) & 0x1);
    HasFMA4 = IsAMD && ((ECX >> 16) & 0x1);
  }
}
