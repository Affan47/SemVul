do_decompress(int infd, int outfd)
{
    struct redup *red;
    u8 *buf, *frame;
    int n;
    int bufsz = BLOCKSZ;

    buf = malloc(bufsz);
    frame = malloc(bufsz);
    if (!buf || !frame) die("malloc(%d): %s\n", bufsz, strerror(errno));

    red = new_redup_stream(infd, outfd);

    if ((n = read(infd, frame, bufsz)) == -1)
        die("read: %s\n", strerror(errno));
    red->inpos += n;

    red_header(red, frame);

    while ((n = read(infd, buf, bufsz)) > 0) {
        if (n < bufsz)
            die("Short read (expected %d got %d)\n", bufsz, n);
        red->framepos = red->inpos;
        red->inpos += n;
        if (o_verbose > 5)
            hexdump(stderr, buf, bufsz);
        red_frame(red, buf);
    }
    if (n == -1)
        die("read:%s\n", strerror(errno));

    end_redup_stream(red);

    return 0;
}
