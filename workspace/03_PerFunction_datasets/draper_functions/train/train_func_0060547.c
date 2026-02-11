cob_memcpy (cob_field *dst, unsigned char *src, const int size)
{
	cob_field	temp;
	cob_field_attr	attr;

	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);
	temp.size = size;
	temp.data = src;
	temp.attr = &attr;
	cob_move (&temp, dst);
}
