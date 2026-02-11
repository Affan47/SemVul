sort_cmp_double(const void *a, const void *b) {
	double va=static_cast<const Table_seq_item *>(a)->value.d;
	double vb=static_cast<const Table_seq_item *>(b)->value.d;
	if(va<vb)
		return -1;
	else if(va>vb)
		return +1;
	else
		return 0;
}
