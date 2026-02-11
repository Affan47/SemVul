search_ptr_table (MonoImage *image, int table, int idx)
{
	MonoTableInfo *ptrdef = &image->tables [table];
	int i;


	for (i = 0; i < ptrdef->rows; i ++)

		if (mono_metadata_decode_row_col (ptrdef, i, 0) == idx)
			break;

	if (i < ptrdef->rows)
		return i + 1;
	else
		return idx;
}
