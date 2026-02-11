expand_filename(const char *name, const char *hbf_name)
{
#ifdef unix
reg	char	*s;
reg	int	size;

	size = name[0] != '/' && (s = strrchr(hbf_name, '/')) != NULL ?
		s - hbf_name + 1 : 0;
	s = malloc((unsigned)size + strlen(name) + 1);
	(void)sprintf(s, "%.*s%s", size, hbf_name, name);
	return s;
#else
#ifdef msdos
reg	char	*s;
reg	int	size;

#ifdef __EMX__
	s = (unsigned char *)hbf_name + strlen((unsigned char *)hbf_name) - 1;
	for(;;) {
		if (*s == '\\' || *s == '/')
			break;
		if (s == hbf_name) {
			s = NULL;
			break;
		}
		s--;
	}

	size = HasDrive(name) ? 0 :
		(name[0] == '\\' || name[0] == '/') ?
			(HasDrive(hbf_name) ? 2 : 0) :
		s != NULL ? s - hbf_name + 1 : 0;
#else
	size = HasDrive(name) ? 0 :
		name[0] == '\\' ? (HasDrive(hbf_name) ? 2 : 0) :
		(s = strrchr(hbf_name, '\\')) != NULL ?
			s - hbf_name + 1 : 0;
#endif
	s = malloc((unsigned)size + strlen(name) + 1);
	(void)sprintf(s, "%.*s%s", size, hbf_name, name);
	return s;
#else
#ifdef vms
reg	char	*s;
reg	const	char	*copyto;
reg	int	size;

	if ((s = strchr(hbf_name, ']')) != NULL && RelativeFileName(name))
		return concat(hbf_name, (s - hbf_name) + 1, name);

	copyto = hbf_name;
	if ((s = strstr(copyto, "::")) != NULL && strstr(name, "::") == NULL)
		copyto = s+2;
	if ((s = strchr(copyto, ':')) != NULL && strchr(name, ':') == NULL)
		copyto = s+1;
	size = copyto - hbf_name;
	s = malloc((unsigned)size + strlen(name) + 1);
	(void)sprintf(s, "%.*s%s", size, hbf_name, name);
	return s;
#else
	return strdup(name);
#endif
#endif
#endif
}
