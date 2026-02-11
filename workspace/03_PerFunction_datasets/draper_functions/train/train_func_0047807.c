getArglistFromFilePos(MIOPos startPosition, const char *tokenName)
{
	MIOPos originalPosition;
	char *result = NULL;
	char *arglist = NULL;
	long pos1, pos2;

	pos2 = mio_tell(File.mio);

	mio_getpos(File.mio, &originalPosition);
	mio_setpos(File.mio, &startPosition);
	pos1 = mio_tell(File.mio);

	if (pos2 > pos1)
	{
		size_t len = pos2 - pos1;

		result = (char *) g_malloc(len + 1);
		if (result != NULL && (len = mio_read(File.mio, result, 1, len)) > 0)
		{
			result[len] = '\0';
			arglist = getArglistFromStr(result, tokenName);
		}
		g_free(result);
	}
	mio_setpos(File.mio, &originalPosition);
	return arglist;
}
