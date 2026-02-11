read_data (void *buf, size_t count)
{
    ssize_t n_read;

    n_read = read (from_daemon_output, buf, count);
    if (n_read < 0)
        g_printerr ("Error reading from daemon: %s\n", strerror (errno));

    return n_read;
}
