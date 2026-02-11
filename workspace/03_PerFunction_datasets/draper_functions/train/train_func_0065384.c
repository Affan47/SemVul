test_read_timeout_slow_writer(int fd)
{
    char buf[] = "OH NO!";


    sleep(2);

    if (write(fd, buf, strlen(buf)+1) == -1) {
	exit(1);
    }
    close(fd);
}
