FixEndingSlash(char *str)
{
#ifdef _WIN32
	if (str[strlen(str)-1]!='/' && str[strlen(str)-1]!='\\')
	{
		strcat(str, "\\");
		return true;
	}
#else
	if (str[strlen(str)-1]!='\\' && str[strlen(str)-1]!='/')
	{
		strcat(str, "/");
		return true;
	}
#endif

	return false;
}
