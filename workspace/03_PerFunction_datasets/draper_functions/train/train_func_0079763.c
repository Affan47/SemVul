sgetenv(const char *sstart, const char *send)
{
	char	**envp;
	int	l = send - sstart;

	for  (envp = environ;  *envp;  envp++)
		if  (strncmp(*envp, sstart, l) == 0  &&  (*envp)[l] == '=')
			return  &(*envp)[l+1];
	return  (char *) 0;
}
