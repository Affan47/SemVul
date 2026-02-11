verify_paddr(physaddr_t paddr)
{
	int i, ok;

	if (!machdep->verify_paddr(paddr))
		return FALSE;

	if (!nr_segments)
		return TRUE;

	for (i = ok = 0; i < nr_segments; i++) {
		if ((paddr >= ram_segments[i].start) &&
		    (paddr < ram_segments[i].end)) {
			ok++;
			break;
		}
	}


	if ((paddr >= 0x100000000ULL) &&
	    machine_type("X86_64") &&
	    (THIS_KERNEL_VERSION < LINUX(2,6,13)))
		ok++;

	if (!ok) {
		if (CRASHDEBUG(1))
			console("reject: %llx\n", (ulonglong)paddr);
		return FALSE;
	}

	return TRUE;
}
