wma_decode_frame(WMADecodeContext *s, int32_t *samples)
{
    int ret, i, n, ch, incr;
    int32_t *ptr;
    fixed32 *iptr;


    s->block_num = 0;
    s->block_pos = 0;


    for(;;)
    {
        ret = wma_decode_block(s, samples);
        if (ret < 0)
        {

            DEBUGF("wma_decode_block failed with code %d\n", ret);
            return -1;
        }
        if (ret)
        {
            break;
        }
    }


    n = s->frame_len;
    incr = s->nb_channels;
    for(ch = 0; ch < s->nb_channels; ++ch)
    {
        ptr = samples + ch;
        iptr = &((*s->frame_out)[ch][0]);

        for (i=0;i<n;++i)
        {
            *ptr = (*iptr++);
            ptr += incr;
        }

        memmove(&((*s->frame_out)[ch][0]), &((*s->frame_out)[ch][s->frame_len]),
            s->frame_len * sizeof(fixed32));
    }

    return 0;
}
