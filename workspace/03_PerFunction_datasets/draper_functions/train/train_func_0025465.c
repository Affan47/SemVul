fsrealloc(int size)
{
	int i;

	if (size >= maxfields) {
		i = maxfields;
		maxfields = size + 16;
		Fields = xrealloc(Fields, maxfields * sizeof(Fields[0]));
		for (; i < maxfields; i++) {
			Fields[i].type = VF_SPECIAL;
			Fields[i].string = NULL;
		}
	}

	for (i = size; i < nfields; i++) {
		clrvar(Fields + i);
	}
	nfields = size;
}
