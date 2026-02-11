deletearch(n)
int n;
{
	if (n >= maxarchive) return;
	freearch(&(archivelist[n]));
	memmove((char *)&(archivelist[n]), (char *)&(archivelist[n + 1]),
		(--maxarchive - n) * sizeof(*archivelist));
}
