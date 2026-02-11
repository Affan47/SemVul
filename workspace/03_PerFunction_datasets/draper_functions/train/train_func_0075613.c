Xstrcpy(s1, s2)
char *s1;
CONST char *s2;
{
	int i;

	for (i = 0; s2[i]; i++) s1[i] = s2[i];
	s1[i] = '\0';

	return(&(s1[i]));
}
