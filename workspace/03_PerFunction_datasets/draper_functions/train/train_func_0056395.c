GART_init(void)
{
	char resource[BUFSIZE];
	struct syment *sp;
	struct machine_specific *ms;

	if (!(sp = kernel_symbol_search("gart_resource")))
		return;

	STRUCT_SIZE_INIT(resource, "resource");
	MEMBER_OFFSET_INIT(resource_start, "resource", "start");
	MEMBER_OFFSET_INIT(resource_end, "resource", "end");

	if (VALID_STRUCT(resource) &&
	    VALID_MEMBER(resource_start) &&
	    VALID_MEMBER(resource_end)) {
		if (!readmem(sp->value, KVADDR, resource,
		    SIZE(resource), "GART resource", RETURN_ON_ERROR))
			return;
		ms = machdep->machspec;
		ms->GART_start = ULONG(resource + OFFSET(resource_start));
		ms->GART_end = ULONG(resource + OFFSET(resource_end));
		if (ms->GART_start && ms->GART_end) {
			machdep->flags |= GART_REGION;
			if (CRASHDEBUG(1))
				fprintf(fp, "GART address range: %lx - %lx\n",
					ms->GART_start, ms->GART_end);
		}
	}
}
