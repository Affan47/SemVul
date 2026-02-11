x86_64_verify_paddr(uint64_t paddr)
{
	struct machine_specific *ms;

	if (machdep->flags & GART_REGION) {
		ms = machdep->machspec;
		if (ms->GART_start && ms->GART_end &&
		    (paddr >= ms->GART_start) &&
		    (paddr <= ms->GART_end))
			return FALSE;
	}

	return TRUE;
}
