removehist(n)
int n;
{
	char *tmp;
	int size;

	if (n < 0 || n >= HISTTYPES) return(NULL);
	size = (int)histsize[n];
	if (!history[n] || size > histbufsize[n] || size <= 0) return(NULL);
	if (--histno[n] < (short)0) histno[n] = MAXHISTNO;
	tmp = history[n][0];
	memmove((char *)&(history[n][0]), (char *)&(history[n][1]),
		size * sizeof(char *));
	history[n][size] = NULL;

	return(tmp);
}
