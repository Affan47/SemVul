AtomicOps_Internalx86CPUFeaturesInit() {
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;


  cpuid(eax, ebx, ecx, edx, 0);
  char vendor[13];
  memcpy(vendor, &ebx, 4);
  memcpy(vendor + 4, &edx, 4);
  memcpy(vendor + 8, &ecx, 4);
  vendor[12] = 0;


  cpuid(eax, ebx, ecx, edx, 1);

  int family = (eax >> 8) & 0xf;
  int model = (eax >> 4) & 0xf;
  if (family == 0xf) {
    family += (eax >> 20) & 0xff;
    model += ((eax >> 16) & 0xf) << 4;
  }


  if (strcmp(vendor, "AuthenticAMD") == 0 &&
      family == 15 &&
      32 <= model && model <= 63) {
    AtomicOps_Internalx86CPUFeatures.has_amd_lock_mb_bug = true;
  } else {
    AtomicOps_Internalx86CPUFeatures.has_amd_lock_mb_bug = false;
  }


  AtomicOps_Internalx86CPUFeatures.has_sse2 = ((edx >> 26) & 1);
}
