read_message()
{
char	buf[BUFSIZ];
struct	rfc2045 *p=rfc2045_alloc_ac();
FILE	*tempfp=0;
int	l;

	if (fseek(stdin, 0L, SEEK_END) < 0 ||
		fseek(stdin, 0L, SEEK_SET) < 0)
	{
		tempfp=tmpfile();
	}

	while ((l=fread(buf, 1, sizeof(buf), stdin)) > 0)
	{

		rfc2045_parse(p, buf, l);
		if (tempfp && fwrite(buf, l, 1, tempfp) != 1)
		{
			perror("fwrite");
			exit(1);
		}
	}
	rfc2045_parse_partial(p);

	if (tempfp)
	{
		dup2(fileno(tempfp), 0);
		fclose(tempfp);
	}
	return (p);
}
