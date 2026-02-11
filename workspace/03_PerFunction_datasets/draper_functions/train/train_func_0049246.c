http_sread(void *data, char *buf, avsize_t nbyte)
{
    avssize_t res;
    struct httplocalfile *lf = (struct httplocalfile *) data;

    do {
        res = av_filebuf_read(lf->sockfb, buf, nbyte);
        if(res != 0)
            return res;

        if(av_filebuf_eof(lf->sockfb))
            return 0;

        res = av_filebuf_check(&lf->sockfb, 1, HTTP_READ_TIMEOUT);
        if(res < 0)
            return res;

    } while(res == 1);

    av_log(AVLOG_ERROR, "HTTP: timeout in body");
    return -EIO;
}
