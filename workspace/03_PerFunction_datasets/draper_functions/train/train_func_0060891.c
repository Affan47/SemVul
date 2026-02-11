next_physpage(ulonglong paddr, ulonglong *nextpaddr)
{
	int n;
	ulonglong node_start;
	ulonglong node_end;
	struct node_table *nt;

	for (n = 0; n < vt->numnodes; n++) {
		nt = &vt->node_table[n];
		node_start = nt->start_paddr;
		node_end = nt->start_paddr + (nt->size * PAGESIZE());

		if (paddr >= node_end)
			continue;

		if (paddr < node_start) {
			*nextpaddr = node_start;
			return TRUE;
		}

		if (paddr < node_end) {
			*nextpaddr = paddr + PAGESIZE();
			return TRUE;
		}
	}

	return FALSE;
}
