cob_intr_char (cob_field *srcfield)
{
	int		i;
	cob_field_attr	attr;
	cob_field	field;

	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);
	COB_FIELD_INIT (1, NULL, &attr);
	make_field_entry (&field);

	i = cob_get_int (srcfield);
	if (i < 1 || i > 256) {
		*curr_field->data = 0;
	} else {
		*curr_field->data = i - 1;
	}
	return curr_field;
}
