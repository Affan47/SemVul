openfile(const char *filename)
{
FILE	*fp=openfile_or_pipe(filename, "r");
int	fd=fileno(fp);
off_t	orig_pos;

	if ((orig_pos=lseek(fd, 0L, SEEK_CUR)) == -1 ||
		lseek(fd, 0L, SEEK_END) == -1 ||
		lseek(fd, 0L, SEEK_CUR) == -1 ||
		lseek(fd, orig_pos, SEEK_SET) == -1)
	{
	FILE *t=tmpfile();
	int	c;

		if (!t)
		{
			perror("tmpfile");
			exit(1);
		}

		while ((c=getc(fp)) != EOF)
			putc(c, t);
		if (ferror(fp) || fflush(t)
			|| ferror(t) || fseek(t, 0L, SEEK_SET) == -1)
		{
			perror("write");
			exit(1);
		}
		fclose(fp);
		fp=t;
	}
	return (fp);
}
