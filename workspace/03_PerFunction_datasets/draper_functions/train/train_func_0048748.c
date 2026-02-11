getDefaultOfficialName(_TCHAR* program)
{
	_TCHAR *ch = NULL;


	ch = lastDirSeparator( program );
	if (ch == NULL) ch = program;
	else ch++;

	ch = _tcsdup( ch );
#ifdef _WIN32
	{

		_TCHAR *extension = _tcsrchr(ch, _T_ECLIPSE('.'));
		if (extension != NULL)
		{
			*extension = _T_ECLIPSE('\0');
		}
	}
#endif

#ifndef LINUX
	{
		*ch = _totupper(*ch);
	}
#else
	{
		if (*ch >= 'a' && *ch <= 'z')
		{
			*ch -= 32;
		}
	}
#endif
	return ch;
}
