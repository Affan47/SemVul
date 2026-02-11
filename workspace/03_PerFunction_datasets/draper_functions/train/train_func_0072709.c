search_ushort_p(ulong *bufptr, ulonglong addr, int longcnt, struct searchinfo *si)
{
	int i;
	int cnt = longcnt * (sizeof(long)/sizeof(short));
	ushort *ptr = (ushort *)bufptr;
	ushort mask = si->s_parms.s_ushort.mask;

	for (i = 0; i < cnt; i++, ptr++, addr += sizeof(short)) {
		for (si->val = 0; si->val < si->vcnt; si->val++) {
			if (SEARCHMASK(*ptr) ==
			    SEARCHMASK(si->s_parms.s_ushort.value[si->val])) {
				if (si->context)
					display_with_pre_and_post(ptr, addr, si);
				else
					fprintf(fp, "%llx: %x %s\n", addr, *ptr,
						show_opt_string(si));
			}
                }
	}
	return addr;
}
