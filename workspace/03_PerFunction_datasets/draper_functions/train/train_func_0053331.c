at_decode(int charset, char *dst, char *src, int len, int ucs2_as_utf8)
{
	switch (charset) {

	case AT_CHAR_GSM:
		char_default_alphabet_decode(dst, src, len);
		break;
	case AT_CHAR_HEXGSM:
		char_hex_decode(dst, src, len);
		break;
	case AT_CHAR_UCS2:
		if (ucs2_as_utf8)

			decode_ucs2_as_utf8(dst, src, len);
		else
			char_ucs2_decode(dst, src, len);
		break;
	default:
		memcpy(dst, src, len);
		dst[len] = 0;
		break;
	}
}
