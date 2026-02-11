parse(const Cff *cff, int pos, int nglyphs, ErrorHandler *errh)
{
    const uint8_t *data = cff->data();
    int len = cff->length();

    if (pos + 1 > len)
	return errh->error("FDSelect position out of range"), -EFAULT;

    int format = data[pos];
    if (format == 0) {
	if (pos + 1 + nglyphs > len)
	    return errh->error("FDSelect [format 0] out of range"), -EFAULT;
	_fds = data + pos + 1;
	_my_fds = false;
	return 0;

    } else if (format == 3) {
	int nranges = (data[pos+1] << 8) | data[pos+2];
	if (pos + 3 + 3*nranges + 2 > len)
	    return errh->error("FDSelect [format 3] out of range"), -EFAULT;

	const uint8_t *p = data + pos + 3;
	int last_glyph = (p[3*nranges] << 8) | p[3*nranges + 1];
	if (p[0] || p[1] || last_glyph != nglyphs)
	    return errh->error("FDSelect [format 3] bad values"), -EINVAL;

	_fds = new uint8_t[nglyphs];
	_my_fds = true;
	int curglyph = 0;
	for (; curglyph < nglyphs; p += 3) {
	    int nextglyph = (p[3] << 8) | p[4];
	    if (nextglyph > nglyphs || nextglyph < curglyph)
		return errh->error("FDSelect [format 3] sorting error"), -EINVAL;
	    memset(const_cast<uint8_t *>(_fds + curglyph), p[2], nextglyph - curglyph);
	    curglyph = nextglyph;
	}
	return 0;

    } else
	return errh->error("unknown charset format %d", format), -EINVAL;
}
