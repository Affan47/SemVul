bad_extension(name)
char	*name;
{
	char	*ip,
		*bads;
	size_t	namelen = strlen(name),
		ext_len;

# if defined(UNIX) || defined(MSFILESYSTEM)
#  ifdef DIRECTORY_ADD_SLASH
	if (strcmp(name, "./")==0 || strcmp(name, "../")==0)
		return YES;
#  else
	if (strcmp(name, ".")==0 || strcmp(name, "..")==0)
		return YES;
#  endif
# endif
	for (ip=bads=BadExtensions; *ip!='\0'; bads = ip+1) {
		if ((ip = strchr(bads, ' ')) == NULL)
			ip = bads + strlen(bads);
		ext_len = ip - bads;
		if (ext_len != 0 && ext_len < namelen
# ifdef FILENAME_CASEINSENSITIVE
		&& caseeqn(&name[namelen - ext_len], bads, ext_len))
# else
		&& strncmp(&name[namelen - ext_len], bads, ext_len) == 0)
# endif
			return YES;
	}
	return NO;
}
