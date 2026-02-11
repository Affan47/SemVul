stat_file(char *buffer)
{
    struct stat	stat_buf;

    if (stat(buffer, &stat_buf) < 0)
	return FileTypeBrokenlink;

    if (S_ISDIR(stat_buf.st_mode))
	return FileTypeDirectory;
    if (stat_buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
	return FileTypeExecutable;
    if (S_ISREG(stat_buf.st_mode))
	return FileTypeDocument;
    if (S_ISCHR(stat_buf.st_mode) || S_ISFIFO(stat_buf.st_mode) ||
	S_ISBLK(stat_buf.st_mode) || S_ISSOCK(stat_buf.st_mode))
	return FileTypeSysdoc;

    return FileTypeBrokenlink;
}
