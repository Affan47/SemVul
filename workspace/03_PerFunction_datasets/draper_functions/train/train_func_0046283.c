load_line_grey(u8 *src_bits, u32 x_offset, u32 y_offset, u32 y_pitch, u32 width, u32 height, u8 *dst_bits)
{
	u32 i;
	src_bits += x_offset + y_offset*y_pitch;
	for (i=0; i<width; i++) {
		dst_bits[0] = dst_bits[1] = dst_bits[2] = *src_bits++;
		dst_bits[3] = 0xFF;
		dst_bits+=4;
	}
}
