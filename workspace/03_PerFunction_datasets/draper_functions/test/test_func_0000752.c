new_matrix (int rows, int columns, char *name)


{
	unsigned long size;
	dims *d;
	header *hd=(header *)newram;
	size=matrixsize(rows,columns);
	d=(dims *)make_header(s_matrix,size,name);
	if (d) { d->c=columns; d->r=rows; }
	return hd;
}
