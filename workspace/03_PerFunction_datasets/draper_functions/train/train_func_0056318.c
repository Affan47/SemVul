lsr_write_coordinate(GF_LASeRCodec *lsr, Fixed val, Bool skipable, const char *name)
{
	if (skipable && !val) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		u32 res = lsr_translate_coords(lsr, val, lsr->coord_bits);
		if (skipable) GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, res, lsr->coord_bits, name);
	}
}
