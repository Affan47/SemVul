clear_graphics_4bit(
	unsigned short page,
	unsigned char left,
	unsigned char top,
	unsigned char right,
	unsigned char bottom,
	unsigned char attr
)
{
	unsigned short cols;
	unsigned short x;
	unsigned short y;
	unsigned long offset;

	cols = var_get(vid_columns);

       	outw( 0x0005, 0x3ce);
	outw( 0x0f02, 0x3c4);
	outw( (attr % 16) << 8, 0x3ce);
	outw( 0x0f01, 0x3ce);
	outw( 0xff08, 0x3ce);
	for (y = top * 16; y < (bottom + 1) * 16; y++) {
		offset = y * cols + left;
		for (x = left; x <= right; x++) {
			put_byte(0xa000, (unsigned char *) offset, attr);
			offset++;
		}
	}
}
