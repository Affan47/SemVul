stripwhite (string)
     char *string;
{
	register int i = 0;


	while (jacl_whitespace (string[i])) i++;

	if (i) strcpy (string, string + i);

	i = strlen (string) - 1;

	while (i >= 0 && (jacl_whitespace (string[i]) || string[i] == '\n' || string[i] == '\r')) i--;

#ifdef WIN32
	string[++i] = '\r';
#endif
	string[++i] = '\n';
	string[++i] = '\0';
}
