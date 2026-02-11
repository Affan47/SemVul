getProgramDir( )
{
	_TCHAR*  ch;
	_TCHAR*  programDir;
	if (program == NULL)
		return NULL;
    programDir = malloc( (_tcslen( program ) + 1) * sizeof(_TCHAR) );
    _tcscpy( programDir, program );
    ch = lastDirSeparator( programDir );
	if (ch != NULL)
    {
    	*(ch+1) = _T_ECLIPSE('\0');
   		return programDir;
    }

    free( programDir );
    return NULL;
}
