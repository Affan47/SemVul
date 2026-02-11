GC_repeat_read(int fd, char *buf, size_t count)
{
    ssize_t num_read = 0;
    ssize_t result;

    while (num_read < count) {
	result = READ(fd, buf + num_read, count - num_read);
	if (result < 0) return result;
	if (result == 0) break;
	num_read += result;
    }
    return num_read;
}
