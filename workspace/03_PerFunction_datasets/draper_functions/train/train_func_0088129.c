ARTreadfile(name)
    char		*name;
{
    static BUFFER	File;
    struct stat		Sb;
    int			fd;
    int			oerrno;


    if ((fd = open(name, O_RDONLY)) < 0)
	return NULL;
    if (fstat(fd, &Sb) < 0) {
	oerrno = errno;
	(void)close(fd);
	errno = oerrno;
	return NULL;
    }


    if (File.Size == 0) {
	File.Size = Sb.st_size;
	File.Data = NEW(char, File.Size + 1);
    }
    else if (File.Size <= Sb.st_size) {
	File.Size = Sb.st_size + 16;
	RENEW(File.Data, char, File.Size + 1);
    }


    if (xread(fd, File.Data, Sb.st_size) < 0) {
	oerrno = errno;
	(void)close(fd);
	errno = oerrno;
	return NULL;
    }


    File.Data[Sb.st_size] = '\0';
    (void)close(fd);
    return File.Data;
}
