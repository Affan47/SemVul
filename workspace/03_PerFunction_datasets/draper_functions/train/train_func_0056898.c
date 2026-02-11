indirect_move (void (*func) (cob_field *src, cob_field *dst),
	       cob_field *src, cob_field *dst, size_t size, int scale)
{
	cob_field	temp;
	cob_field_attr	attr;
	unsigned char	data[64];

	COB_ATTR_INIT (COB_TYPE_NUMERIC_DISPLAY, size, scale,
			COB_FLAG_HAVE_SIGN, NULL);
	temp.size = size;
	temp.data = data;
	temp.attr = &attr;
	func (src, &temp);
	cob_move (&temp, dst);
}
