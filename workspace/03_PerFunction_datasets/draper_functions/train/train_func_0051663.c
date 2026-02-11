hash(char *ss)
{
	int	i;
	unsigned char 	*s = (unsigned char *)ss;

	for (i = 0; *s != '\0'; )
		i += *s++;
	return(i);
}
