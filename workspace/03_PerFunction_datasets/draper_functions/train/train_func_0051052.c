IsMaildir(const char *name)
{
Buffer	dirname;
Buffer	subdirname;
struct	stat stat_buf;

int	c;

	if (!name || !*name)	return (0);
	dirname=name;
	c=dirname.pop();
	if (c != SLASH_CHAR)	dirname.push(c);
	subdirname=dirname;
	subdirname += "/tmp";
	subdirname += '\0';
	if ( stat( (const char *)subdirname, &stat_buf ) ||
		! S_ISDIR(stat_buf.st_mode) )	return (0);
	subdirname=dirname;
	subdirname += "/new";
	subdirname += '\0';
	if ( stat( (const char *)subdirname, &stat_buf ) ||
		! S_ISDIR(stat_buf.st_mode) )	return (0);
	subdirname=dirname;
	subdirname += "/cur";
	subdirname += '\0';
	if ( stat( (const char *)subdirname, &stat_buf ) ||
		! S_ISDIR(stat_buf.st_mode) )	return (0);
	return (1);
}
