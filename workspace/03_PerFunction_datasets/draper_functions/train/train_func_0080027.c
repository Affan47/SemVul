open_temp(gboolean write)
{
    int fd = open(temp_filename, write? O_WRONLY|O_CREAT|O_TRUNC : O_RDONLY, 0777);
    if (fd < 0) {
	perror("open temporary file");
	exit(1);
    }

    return fd;
}
