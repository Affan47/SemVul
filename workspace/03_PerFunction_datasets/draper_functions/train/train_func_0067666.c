endian_to_uint(bool is_big, const uchar *b ) {
	return is_big?x_endian_to_uint(b[3], b[2], b[1], b[0]):
		x_endian_to_uint(b[0], b[1], b[2], b[3]);
}
