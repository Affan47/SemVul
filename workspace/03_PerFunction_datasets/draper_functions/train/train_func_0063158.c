mono_hwcap_arch_init (void)
{
	int eax, ebx, ecx, edx;

	if (cpuid (1, &eax, &ebx, &ecx, &edx)) {
		if (edx & (1 << 15)) {
			mono_hwcap_x86_has_cmov = TRUE;

			if (edx & 1)
				mono_hwcap_x86_has_fcmov = TRUE;
		}

		if (edx & (1 << 25))
			mono_hwcap_x86_has_sse1 = TRUE;

		if (edx & (1 << 26))
			mono_hwcap_x86_has_sse2 = TRUE;

		if (ecx & (1 << 0))
			mono_hwcap_x86_has_sse3 = TRUE;

		if (ecx & (1 << 9))
			mono_hwcap_x86_has_ssse3 = TRUE;

		if (ecx & (1 << 19))
			mono_hwcap_x86_has_sse41 = TRUE;

		if (ecx & (1 << 20))
			mono_hwcap_x86_has_sse42 = TRUE;
	}

	if (cpuid (0x80000000, &eax, &ebx, &ecx, &edx)) {
		if ((unsigned int) eax >= 0x80000001 && ebx == 0x68747541 && ecx == 0x444D4163 && edx == 0x69746E65) {
			if (cpuid (0x80000001, &eax, &ebx, &ecx, &edx)) {
				if (ecx & (1 << 6))
					mono_hwcap_x86_has_sse4a = TRUE;
			}
		}
	}

#if defined(HAVE_UNISTD_H)
	mono_hwcap_x86_is_xen = !access ("/proc/xen", F_OK);
#endif
}
