adsi_rx(adsi_rx_state_t *s, const int16_t *amp, int len)
{
    switch (s->standard)
    {
    case ADSI_STANDARD_CLIP_DTMF:

        s->in_progress -= len;
        if (s->in_progress <= 0)
            s->msg_len = 0;
        dtmf_rx(&(s->dtmfrx), amp, len);
        break;
    default:
        fsk_rx(&(s->fskrx), amp, len);
        break;
    }
    return 0;
}
