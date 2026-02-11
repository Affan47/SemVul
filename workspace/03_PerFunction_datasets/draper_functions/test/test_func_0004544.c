oss_read(void *self, ref_buffer *rb)
{
    int result;
    im_oss_state *s = self;

    rb->buf = malloc(BUFSIZE*2*s->channels);
    if(!rb->buf)
        return -1;
    result = read(s->fd, rb->buf, BUFSIZE*2*s->channels);

    rb->len = result;
    rb->aux_data = s->rate*s->channels*2;

    if(s->newtrack)
    {
        rb->critical = 1;
        s->newtrack = 0;
    }

    if(result == -1 && (errno == EINTR || errno == ERESTART))
    {
        return 0;
    }
    else if(result <= 0)
    {
        if(result == 0)
            LOG_INFO0("Reached EOF, no more data available");
        else
            LOG_ERROR1("Error reading from audio device: %s", strerror(errno));
        free(rb->buf);
        return -1;
    }

    return rb->len;
}
