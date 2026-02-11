endian_to_ushort(bool is_big, const uchar *b) {
	return is_big?x_endian_to_ushort(b[1], b[0]):
		x_endian_to_ushort(b[0], b[1]);
}
