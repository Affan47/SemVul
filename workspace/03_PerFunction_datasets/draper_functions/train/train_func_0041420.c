shift_overflows(size_t num, unsigned bits)
{
	if (bits == 0) {
		return false;
	}

	return ((num << bits) >> 1) != (num << (bits - 1));
}
