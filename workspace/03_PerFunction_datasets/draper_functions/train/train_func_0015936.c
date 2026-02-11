bJustifyCenter (bstring b, int width, int space) {
int ret;
	if (width <= 0) return -__LINE__;
	if (0 > (ret = bJustifyLeft (b, space))) return ret;
	if (b->slen <= width)
		return bInsertChrs (b, 0, (width - b->slen + 1) >> 1, (unsigned char) space, (unsigned char) space);
	return BSTR_OK;
}
