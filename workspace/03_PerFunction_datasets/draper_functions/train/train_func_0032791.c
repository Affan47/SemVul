strndel(char *s, int p, int n)
{
	for (; (*(s+p) = *(s+p+n)) != '\0'; s++ )
		*(s+p+n) = '\0';
}
