Term_addREGEX(CTX ctx, kTerm *tkB, CWB_t *cwb, kInputStream *in, kline_t *ul, int ch0)
{
	int prev = 0;
	int ch = (ch0 == 0) ? knh_InputStream_getc(ctx, in) : ch0;
	do {
		if(ch == '\n') {
			WARN_MustCloseWith(ctx, '/');
			Term_addBuf(ctx, tkB, cwb, TT_ch('/'), ch);
			return ch;
		}
		if(ch == '/') {
			if(prev != '\\') break;
			knh_Bytes_reduce(cwb->ba, 1);
		}
		knh_Bytes_putc(ctx, cwb->ba, ch);
		if(prev == '\\' && ch == '\\') ch = 0;
		prev = ch;
	} while((ch = knh_InputStream_getc(ctx, in)) != EOF);
	ch = knh_InputStream_getc(ctx, in);
	Term_addBuf(ctx, tkB, cwb, TT_ch('/'), ch);
	return ch;
}
