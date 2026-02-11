init_sample_buffers(AlacEncodeContext *s, int16_t *input_samples)
{
    int ch, i;

    for(ch=0;ch<s->avctx->channels;ch++) {
        int16_t *sptr = input_samples + ch;
        for(i=0;i<s->avctx->frame_size;i++) {
            s->sample_buf[ch][i] = *sptr;
            sptr += s->avctx->channels;
        }
    }
}
