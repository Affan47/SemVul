am_remove_feature(
    am_feature_t	*f,
    am_feature_e	n)
{
    size_t			byte;
    int				bit;
    int				result = 0;

    if (f != NULL && (int)n >= 0) {
	byte = ((size_t)n) >> 3;
	if (byte < f->size) {
	    bit = ((int)n) & 0x7;
	    f->bytes[byte] = (unsigned char)((int)f->bytes[byte] & (unsigned char)~(1 << bit));
	    result = 1;
	}
    }
    return result;
}
