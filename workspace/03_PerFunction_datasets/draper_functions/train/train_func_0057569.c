print_message(FILE *datfile, FILE *fp, int fullmsg)
{
char	buf[BUFSIZ];

	if (fseek(datfile, 0L, SEEK_SET) == -1)	return (-1);

	while (fgets(buf, sizeof(buf), datfile))
	{
		if (!fullmsg && (
			buf[0] == '\n' || (buf[0] == '\r' && buf[1] == '\n')))
			break;
		fprintf(fp, "%s", buf);
		if (strchr(buf, '\n') == 0)
		{
		int	c;

			while ((c=getc(datfile)) >= 0)
			{
				putc(c, fp);
				if (c == '\n')	break;
			}
		}
	}
	return (0);
}
