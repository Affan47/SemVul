downmix_buffer_float(downmix_state *s, float **buf, int samples)
{
    int i;

    if(samples > s->buflen) {
        void *tmp = realloc(s->buffer, samples * sizeof(float));
        if (tmp==NULL)
            return;
        s->buffer = tmp;
        s->buflen = samples;
    }

    for(i=0; i < samples; i++) {
        s->buffer[i] = (buf[0][i] + buf[1][i])*0.5;
    }

}
