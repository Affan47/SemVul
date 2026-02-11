kdb_getword(unsigned long *word, unsigned long addr, size_t size)
{
	int diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*word = 0;
	switch (size) {
	case 1:
		diag = kdb_getarea(w1, addr);
		if (!diag)
			*word = w1;
		break;
	case 2:
		diag = kdb_getarea(w2, addr);
		if (!diag)
			*word = w2;
		break;
	case 4:
		diag = kdb_getarea(w4, addr);
		if (!diag)
			*word = w4;
		break;
	case 8:
		if (size <= sizeof(*word)) {
			diag = kdb_getarea(w8, addr);
			if (!diag)
				*word = w8;
			break;
		}

	default:
		diag = KDB_BADWIDTH;
		kdb_printf("kdb_getword: bad width %ld\n", (long) size);
	}
	return diag;
}
