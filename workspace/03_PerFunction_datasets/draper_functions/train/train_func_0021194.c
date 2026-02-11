gsf_input_stdio_seek (GsfInput *input, gsf_off_t offset, GSeekType whence)
{
	GsfInputStdio const *stdio = GSF_INPUT_STDIO (input);
	int stdio_whence = SEEK_SET;

#ifndef HAVE_FSEEKO
	long loffset;
#else
	off_t loffset;
#endif

	if (stdio->file == NULL)
		return TRUE;

	loffset = offset;
	if ((gsf_off_t) loffset != offset) {
#ifdef HAVE_FSEEKO
		g_warning ("offset too large for fseeko");
#else
		g_warning ("offset too large for fseek");
#endif
		return TRUE;
	}
	switch (whence) {
	case G_SEEK_CUR : stdio_whence = SEEK_CUR; break;
	case G_SEEK_END : stdio_whence = SEEK_END; break;
	case G_SEEK_SET:
	default:
		break;
	}

	errno = 0;
#ifdef HAVE_FSEEKO
	if (0 == fseeko (stdio->file, loffset, stdio_whence))
		return FALSE;
#else
	if (0 == fseek (stdio->file, loffset, stdio_whence))
		return FALSE;
#endif

	return TRUE;
}
