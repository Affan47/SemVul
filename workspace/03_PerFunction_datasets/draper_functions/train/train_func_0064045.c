t38_gateway_init(t38_gateway_state_t *s,
                                      t38_tx_packet_handler_t *tx_packet_handler,
                                      void *tx_packet_user_data)
{
    if (tx_packet_handler == NULL)
        return NULL;

    if (s == NULL)
    {
        if ((s = (t38_gateway_state_t *) malloc(sizeof(*s))) == NULL)
            return NULL;
    }
    memset(s, 0, sizeof(*s));
    span_log_init(&s->logging, SPAN_LOG_NONE, NULL);
    span_log_set_protocol(&s->logging, "T.38G");

    t38_gateway_audio_init(s);
    t38_gateway_t38_init(s, tx_packet_handler, tx_packet_user_data);

    set_rx_active(s, TRUE);
    t38_gateway_set_supported_modems(s, T30_SUPPORT_V27TER | T30_SUPPORT_V29);
    t38_gateway_set_nsx_suppression(s, (const uint8_t *) "\x00\x00\x00", 3, (const uint8_t *) "\x00\x00\x00", 3);

    s->ecm_allowed = FALSE;
    restart_rx_modem(s);
#if defined(LOG_FAX_AUDIO)
    {
        char buf[100 + 1];
        struct tm *tm;
        time_t now;

        time(&now);
        tm = localtime(&now);
        sprintf(buf,
                "/tmp/t38-rx-audio-%p-%02d%02d%02d%02d%02d%02d",
                s,
                tm->tm_year%100,
                tm->tm_mon + 1,
                tm->tm_mday,
                tm->tm_hour,
                tm->tm_min,
                tm->tm_sec);
        s->audio.fax_audio_rx_log = open(buf, O_CREAT | O_TRUNC | O_WRONLY, 0666);
        sprintf(buf,
                "/tmp/t38-tx-audio-%p-%02d%02d%02d%02d%02d%02d",
                s,
                tm->tm_year%100,
                tm->tm_mon + 1,
                tm->tm_mday,
                tm->tm_hour,
                tm->tm_min,
                tm->tm_sec);
        s->audio.fax_audio_tx_log = open(buf, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    }
#endif
    return s;
}
