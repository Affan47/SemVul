icx_noofinks(inkmask mask) {
	int i, count = 0;

	for (i = 0; icx_ink_table[i].m != 0; i++) {
		if (mask & icx_ink_table[i].m) {
			count++;
		}
	}
	return count;
}
