char_uni_alphabet_decode(wchar_t value, unsigned char *dest, MBSTATE *mbs)
{
	int length;

    switch (length = char_wctomb(dest, value, mbs)) {
	case -1:
		*dest = '?';
		length = 1;
	default:
		return length;
	}
}
