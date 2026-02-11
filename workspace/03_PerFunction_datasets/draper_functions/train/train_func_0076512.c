flic_probe(AVProbeData *p)
{
    int magic_number;

    if(p->buf_size < FLIC_HEADER_SIZE)
        return 0;

    magic_number = AV_RL16(&p->buf[4]);
    if ((magic_number != FLIC_FILE_MAGIC_1) &&
        (magic_number != FLIC_FILE_MAGIC_2) &&
        (magic_number != FLIC_FILE_MAGIC_3))
        return 0;

    if(AV_RL16(&p->buf[0x10]) != FLIC_CHUNK_MAGIC_1){
        if(AV_RL32(&p->buf[0x10]) > 2000)
            return 0;
    }

    if(   AV_RL16(&p->buf[0x08]) > 4096
       || AV_RL16(&p->buf[0x0A]) > 4096)
        return 0;


    return AVPROBE_SCORE_MAX;
}
