fixup_labels(F_ARRAY *labels, CELL code_format, F_CODE_BLOCK *compiled)
{
	CELL i;
	CELL size = array_capacity(labels);

	for(i = 0; i < size; i += 3)
	{
		CELL class = to_fixnum(array_nth(labels,i));
		CELL offset = to_fixnum(array_nth(labels,i + 1));
		CELL target = to_fixnum(array_nth(labels,i + 2));

		store_address_in_code_block(class,
			offset + (CELL)(compiled + 1),
			target + (CELL)(compiled + 1));
	}
}
