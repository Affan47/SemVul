file_length()
{
    off64_t current, length;

    if (!regular_file)
	return 0x7FFFFFFF;

    current = lseek64(fd, 0, SEEK_CUR);
    length  = lseek64(fd, 0, SEEK_END);
    lseek64(fd, current, SEEK_SET);
    return length;
}
