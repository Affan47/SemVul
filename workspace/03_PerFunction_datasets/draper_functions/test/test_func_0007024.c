scanSeparators (char* name)
{
	char sep = name [0];
	char *copyto = name;
	boolean quoted = FALSE;

	for (++name ; *name != '\0' ; ++name)
	{
		if (quoted)
		{
			if (*name == sep)
				*copyto++ = sep;
			else if (*name == 't')
				*copyto++ = '\t';
			else
			{

				*copyto++ = '\\';
				*copyto++ = *name;
			}
			quoted = FALSE;
		}
		else if (*name == '\\')
			quoted = TRUE;
		else if (*name == sep)
		{
			break;
		}
		else
			*copyto++ = *name;
	}
	*copyto = '\0';
	return name;
}
