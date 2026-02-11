filebuf_lineend(struct filebuf *fb)
{
    avssize_t res;
    char *start;
    char *s;

    do {
        start = fb->buf + fb->ptr;
        if(fb->nbytes > 0) {
            s = memchr(start, '\n', fb->nbytes);
            if(s != NULL)
                return (s + 1) - start;
        }

        if(fb->eof)
            return fb->nbytes;

        res = read_data(fb);
    } while(res > 0);

    return res;
}
