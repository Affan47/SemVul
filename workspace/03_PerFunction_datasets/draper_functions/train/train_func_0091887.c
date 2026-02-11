Xsetlinebuf(fp)
XFILE *fp;
{
	if (fp && (fp == Xstdout || fp == Xstderr)) {
		VOID_C flushbuf(fp);
		fp -> flags |= XF_LINEBUF;
		fp -> flags &= ~XF_NOBUF;
	}
}
