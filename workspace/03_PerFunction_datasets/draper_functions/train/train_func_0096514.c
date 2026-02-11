rightmost_1 (uint64_t *m, int max_i){
	int block = max_i / 64;

	while (block > 0 && m[block] == 0)  block--;
	if (m[block] == 0) return -1;


#ifdef USE_ASM_BITSCAN
	return ( _bitscan(m[block])) + 64 * block;
#else

	uint64_t x = m[block];

	int pos = 0;
	while ((x & (1ull << 63)) == 0){
		pos++;
		x = x << 1;
	}
	int res =  (63 - pos) + 64 * block;
	return res;
#endif
}
