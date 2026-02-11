stripAbsolute (const unsigned char *filename)
{
	const unsigned char *tmp;


	if (*filename == '/' || *filename == '\\')
	{
		boolean skipSlash = TRUE;

		tmp = (const unsigned char*) strrchr ((const char*) filename,  '/');
		if (tmp == NULL)
		{
			tmp = (const unsigned char*) strrchr ((const char*) filename, '\\');
			if (tmp == NULL)
			{
				tmp = filename;
				skipSlash = FALSE;
			}
		}


		if (skipSlash)
			tmp++;
	}
	else
		tmp = filename;

	return tmp;
}
