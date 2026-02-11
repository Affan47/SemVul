Init_DEEP_Tabs(void){
	USHORT i, j;

	for (i = 0; i < N_CHAR; i++) {
		freq[i] = 1;
		son[i] = (USHORT)(i + T);
		prnt[i + T] = i;
	}
	i = 0; j = N_CHAR;
	while (j <= R) {
		freq[j] = (USHORT) (freq[i] + freq[i + 1]);
		son[j] = i;
		prnt[i] = prnt[i + 1] = j;
		i += 2; j++;
	}
	freq[T] = 0xffff;
	prnt[R] = 0;

	dms_init_deep_tabs = 0;
}
