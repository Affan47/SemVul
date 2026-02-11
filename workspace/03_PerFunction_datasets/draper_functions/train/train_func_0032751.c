Open()
{
	Close();
	fp=tmpfile();
	if (fp == 0)	return (-1);
	fd=fileno(fp);
	return (fd);
}
