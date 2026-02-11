icx_index2ink(inkmask mask, int ixno) {
	int i, count = 0;

	for (i = 0; icx_ink_table[i].m != 0; i++) {
		if (mask & icx_ink_table[i].m) {
			if (ixno == count)
				return icx_ink_table[i].m;
			count++;
		}
	}
	return 0;
}
