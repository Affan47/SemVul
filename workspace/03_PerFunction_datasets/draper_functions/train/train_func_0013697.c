knh_write_flag(CTX ctx, kOutputStream *w, kflag_t flag)
{
	kchar_t ubuf[8];
	kbytes_t t = {{(const char*)ubuf}, 1};
	kintptr_t i;
	kflag_t f = 1 << 15;
	for(i = 0; i < 16; i++) {
		if(i > 0 && i % 8 == 0) {
			ubuf[0] = ' ';
			io2_write(ctx, w->io2, t.text, 1);
		}
		ubuf[0] = ((f & flag) == f) ? '1' : '0';
		io2_write(ctx, w->io2, t.text, 1);
		f = f >> 1;
	}
}
