bdelete (bstring b, int pos, int len) {

	if (pos < 0) {
		len += pos;
		pos = 0;
	}

	if (len < 0 || b == NULL || b->data == NULL || b->slen < 0 ||
	    b->mlen < b->slen || b->mlen <= 0)
		return BSTR_ERR;
	if (len > 0 && pos < b->slen) {
		if (pos + len >= b->slen) {
			b->slen = pos;
		} else {
			bBlockCopy ((char *) (b->data + pos),
			            (char *) (b->data + pos + len),
			            b->slen - (pos+len));
			b->slen -= len;
		}
		b->data[b->slen] = (unsigned char) '\0';
	}
	return BSTR_OK;
}
