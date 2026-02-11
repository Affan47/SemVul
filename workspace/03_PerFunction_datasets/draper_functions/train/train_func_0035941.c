_GraceFlush(void)
{
    int loop, left;

    if (fd_pipe == -1) {
        return (-1);
    }

    left = strlen(buf);

    for (loop = 0; loop < 30; loop++) {
        left = GraceOneWrite(left);
        if (left < 0) {
            return (-1);
        } else if (left == 0) {
            return (0);
        }
    }

    error_function("GraceFlush: ran into eternal loop");

    return (-1);
}
