cpuid_is_family_p4(void)
{
   cpuid_version_t v = cpuid_get_version();

   return cpuid_is_vendor_intel() && v.bits.family == CPUID_FAMILY_EXTENDED &&
      v.bits.extendedFamily == CPUID_EXTENDED_FAMILY_PENTIUM4;
}
