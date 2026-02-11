FcStrCanonFilename (const FcChar8 *s)
{
#ifdef _WIN32
    FcChar8 full[FC_MAX_FILE_LEN + 2];
    int size = GetFullPathName (s, sizeof (full) -1,
				full, NULL);

    if (size == 0)
	perror ("GetFullPathName");

    FcConvertDosPath (full);
    return FcStrCanonAbsoluteFilename (full);
#else
    if (s[0] == '/')
	return FcStrCanonAbsoluteFilename (s);
    else
    {
	FcChar8	*full;
	FcChar8 *file;

	FcChar8	cwd[FC_MAX_FILE_LEN + 2];
	if (getcwd ((char *) cwd, FC_MAX_FILE_LEN) == NULL)
	    return NULL;
	strcat ((char *) cwd, "/");
	full = FcStrPlus (cwd, s);
	file = FcStrCanonAbsoluteFilename (full);
	FcStrFree (full);
	return file;
    }
#endif
}
