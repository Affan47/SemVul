ti_readline(BGZF *fp, kstring_t *str)
{
	int l, state = 0;
	unsigned char *buf = (unsigned char*)fp->uncompressed_block;
	str->l = 0;
	do {
		if (fp->block_offset >= fp->block_length) {
			if (bgzf_read_block(fp) != 0) { state = -2; break; }
			if (fp->block_length == 0) { state = -1; break; }
		}
		for (l = fp->block_offset; l < fp->block_length && buf[l] != '\n'; ++l);
		if (l < fp->block_length) state = 1;
		l -= fp->block_offset;
		if (str->l + l + 1 >= str->m) {
			str->m = str->l + l + 2;
			kroundup32(str->m);
			str->s = (char*)realloc(str->s, str->m);
		}
		memcpy(str->s + str->l, buf + fp->block_offset, l);
		str->l += l;
		fp->block_offset += l + 1;
		if (fp->block_offset >= fp->block_length) {
#ifdef _USE_KNETFILE
			fp->block_address = knet_tell(fp->x.fpr);
#else
			fp->block_address = ftello(fp->file);
#endif
			fp->block_offset = 0;
			fp->block_length = 0;
		}
	} while (state == 0);
	if (str->l == 0 && state < 0) return state;
	str->s[str->l] = 0;
	return str->l;
}
