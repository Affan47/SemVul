Bytes_addESC(CTX ctx, kBytes *ba, kInputStream *in, kline_t *ul)
{
	int ch = knh_InputStream_getc(ctx, in);
	if(ch == 'n') ch = '\n';
	else if(ch == 't') ch = '\t';
	else if(ch == 'r') ch = '\r';

	knh_Bytes_putc(ctx, ba, ch);
}
