is_garbage_table(void) {
	int i;

	for (i = 0; i < 4; i++) {
		struct pte *pe = &ptes[i];
		struct partition *p = pe->part_table;

		if (p->boot_ind != 0 && p->boot_ind != 0x80)
			return 1;
	}
	return 0;
}
