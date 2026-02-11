fso_flush_i(OutStream *os, const uchar *src, int len)
{
    if (len != write(os->file.fd, src, len)) {
        RAISE(IO_ERROR, "flushing src of length %d, <%s>", len,
              strerror(errno));
    }
}
