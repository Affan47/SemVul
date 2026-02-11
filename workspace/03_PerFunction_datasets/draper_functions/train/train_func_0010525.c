nsv_probe(AVProbeData *p)
{
    int i;


    if (p->buf[0] == 'N' && p->buf[1] == 'S' &&
        p->buf[2] == 'V' && (p->buf[3] == 'f' || p->buf[3] == 's'))
        return AVPROBE_SCORE_MAX;


    for (i = 1; i < p->buf_size - 3; i++) {
        if (p->buf[i+0] == 'N' && p->buf[i+1] == 'S' &&
            p->buf[i+2] == 'V' && p->buf[i+3] == 's')
            return AVPROBE_SCORE_MAX-20;
    }

    if (match_ext(p->filename, "nsv"))
        return AVPROBE_SCORE_MAX/2;

    return 0;
}
