InputStream_skipMultiByteChar(CTX ctx, kInputStream *in, kline_t *ul, int ch)
{
	char buf[8] = {ch, 0};
	int i, size = knh_utf8len(ch);
	if(size > 2) {
		for(i = 1; i < size; i++) {
			ch = knh_InputStream_getc(ctx, in);
			buf[i] = ch;
		}
		WARN_UnxpectedMultiByteChar(ctx, buf);
		return ' ';
	}
	else {
		while((ch = knh_InputStream_getc(ctx, in)) > 127);
		WARN_UnxpectedMultiByteChar(ctx, NULL);
		return ch;
	}
}
