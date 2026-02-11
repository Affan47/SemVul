UT_XML_transNoAmpersands(const gchar * szSource)
{
	static gchar *rszDestBuffer = NULL;
	static UT_uint32 iDestBufferLength = 0;

	if (szSource == NULL)
		return NULL;

	UT_uint32 length = strlen(szSource) + 1;
	if (length > iDestBufferLength) {
		if (rszDestBuffer && iDestBufferLength) {
			g_free(rszDestBuffer);
		}
		iDestBufferLength = 0;
		rszDestBuffer = static_cast<gchar *>(UT_calloc(length, sizeof(gchar)));

		if (!rszDestBuffer)
			return NULL;

		iDestBufferLength = length;
	}
	memset(rszDestBuffer, 0, iDestBufferLength);

	const gchar * o = szSource;
	gchar * n = rszDestBuffer;
	while (*o != 0)
	{
		if (*o != '&')
		{
			*n = *o;
			n++;
		}
		o++;
	}

	return rszDestBuffer;
}
