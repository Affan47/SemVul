stderr_readable(int fd, void *data)
{
    task_waiting_on_exec *tw = data;
    char buffer[1000];
    int n;
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
	stream_add_string(tw->serr, raw_bytes_to_binary(buffer, n));
    }
}
