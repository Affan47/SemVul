xen_strict_xenbus_quirk(void)
{
#ifdef CONFIG_X86
	uint32_t eax, ebx, ecx, edx, base;

	base = xen_cpuid_base();
	cpuid(base + 1, &eax, &ebx, &ecx, &edx);

	if ((eax >> 16) < 4)
		return true;
#endif
	return false;

}
