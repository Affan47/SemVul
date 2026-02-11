cpu_has_feature(int x)
{
    uint32_t level = ((x & 1) << 31) | 1;

    return cpu_has_level(level) && ((cpuid_edx(level) >> (x & 31) & 1));
}
