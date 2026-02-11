read_tree_p(void){
	USHORT i,n;

	n = GETBITS(5);
	DROPBITS(5);
	if (n>0){
		for (i=0; i<n; i++) {
			pt_len[i] = (UCHAR)GETBITS(4);
			DROPBITS(4);
		}
		for (i=n; i<dms_np; i++) pt_len[i] = 0;
		if (dms_make_table(dms_np,pt_len,8,pt_table)) return 1;
	} else {
		n = GETBITS(5);
		DROPBITS(5);
		for (i=0; i<dms_np; i++) pt_len[i] = 0;
		for (i=0; i<256; i++) pt_table[i] = n;
	}
	return 0;
}
