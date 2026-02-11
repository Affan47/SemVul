sparsematrix_count_elements(const sparsematrix_t* sp) {
	int i, N;
	N = 0;
	for (i=0; i<sp->R; i++)
		N += bl_size(sp->rows + i);
	return N;
}
