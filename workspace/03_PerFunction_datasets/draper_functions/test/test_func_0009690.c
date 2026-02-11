first_char(const char *filename)
{
    int fd, rc;
    char c;

    fd = open(filename, O_RDONLY);
    JASSERT(fd >= 0)(filename).Text("ERROR: Cannot open filename");

    rc = _real_read(fd, &c, 1);
    JASSERT(rc == 1)(filename).Text("ERROR: Error reading from filename");

    close(fd);
    return c;
}
