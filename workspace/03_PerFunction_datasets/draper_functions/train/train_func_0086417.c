v8_restart(v8_state_t *s,
                             int calling_party,
                             v8_parms_t *parms)
{
    memcpy(&s->parms, parms, sizeof(s->parms));
    memset(&s->result, 0, sizeof(s->result));

    s->result.call_function = s->parms.call_function;
    s->result.nsf = -1;
    s->result.t66 = -1;

    s->ci_timer = 0;
    if (calling_party)
    {
        s->calling_party = TRUE;
        s->state = V8_WAIT_1S;
        s->negotiation_timer = ms_to_samples(1000);
        s->ci_count = 0;
        modem_connect_tones_rx_init(&s->ansam_rx, MODEM_CONNECT_TONES_ANS_PR, NULL, NULL);
        fsk_tx_init(&s->v21tx, &preset_fsk_specs[FSK_V21CH1], get_bit, s);
    }
    else
    {

        s->calling_party = FALSE;
        modem_connect_tones_tx_init(&s->ansam_tx, s->parms.modem_connect_tone);

        v8_decode_init(s);
        s->state = V8_CM_WAIT;
        s->negotiation_timer = ms_to_samples(200 + 5000);
        s->modem_connect_tone_tx_on = ms_to_samples(75) + 1;
    }
    s->result.modem_connect_tone = MODEM_CONNECT_TONES_NONE;

    if ((s->tx_queue = queue_init(NULL, 1024, 0)) == NULL)
        return -1;
    return 0;
}
