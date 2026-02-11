e_bit_array_selected_count (EBitArray *bit_array)
{
	gint count;
	gint i;
	gint last;

	if (!bit_array->data)
		return 0;

	count = 0;

	last = BOX (bit_array->bit_count - 1);

	for (i = 0; i <= last; i++) {
		gint j;
		guint32 thiscount = 0;
		for (j = 0; j < 8; j++)
			thiscount += PART (bit_array->data[i], j);
		for (j = 0; j < 4; j++)
			count += SECTION (thiscount, j);
	}

	return count;
}
