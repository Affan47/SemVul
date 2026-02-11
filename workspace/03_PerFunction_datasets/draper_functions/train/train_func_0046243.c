bisstemeqblk (const_bstring b0, const void * blk, int len) {
int i;

	if (bdata (b0) == NULL || b0->slen < 0 || NULL == blk || len < 0)
		return BSTR_ERR;
	if (b0->slen < len) return BSTR_OK;
	if (b0->data == (const unsigned char *) blk || len == 0) return 1;

	for (i = 0; i < len; i ++) {
		if (b0->data[i] != ((const unsigned char *) blk)[i]) return BSTR_OK;
	}
	return 1;
}
