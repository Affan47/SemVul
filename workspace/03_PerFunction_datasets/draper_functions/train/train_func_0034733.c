cob_get_int (cob_field *f)
{
	int		n;
	cob_field	temp;
	cob_field_attr	attr;

	switch (COB_FIELD_TYPE (f)) {
	case COB_TYPE_NUMERIC_DISPLAY:
		return cob_display_get_int (f);
	case COB_TYPE_NUMERIC_BINARY:
		return (int)cob_binary_mget_int64 (f);
	case COB_TYPE_NUMERIC_PACKED:
		return cob_packed_get_int (f);
	default:
		COB_ATTR_INIT (COB_TYPE_NUMERIC_BINARY, 9, 0,
				COB_FLAG_HAVE_SIGN, NULL);
		temp.size = 4;
		temp.data = (unsigned char *)&n;
		temp.attr = &attr;
		cob_move (f, &temp);
		return n;
	}
}
