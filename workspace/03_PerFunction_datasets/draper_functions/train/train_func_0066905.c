text_to_parv(char *text, int maxparc, char **parv)
{
	int count = 0;
	char *p;

        if (maxparc == 0)
        	return 0;

	if (!text)
		return 0;

	p = text;
	while (count < maxparc - 1 && (parv[count] = strtok(p, " ")) != NULL)
		count++, p = NULL;

	if ((parv[count] = strtok(p, "")) != NULL)
	{
		p = parv[count];
		while (*p == ' ')
			p++;
		parv[count] = p;
		if (*p != '\0')
		{
			p += strlen(p) - 1;
			while (*p == ' ' && p > parv[count])
				p--;
			p[1] = '\0';
			count++;
		}
	}
	return count;
}
