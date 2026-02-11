process_state_iv_eor(t30_state_t *s, const uint8_t *msg, int len)
{
    switch (msg[2] & 0xFE)
    {
    case T30_RNR:
        if (s->timer_t5 == 0)
            s->timer_t5 = ms_to_samples(DEFAULT_TIMER_T5);
        set_state(s, T30_STATE_IV_EOR_RNR);
        queue_phase(s, T30_PHASE_D_TX);
        send_simple_frame(s, T30_RR);
        break;
    case T30_PIN:
        s->retries = 0;
        if (s->phase_d_handler)
        {
            s->phase_d_handler(s, s->phase_d_user_data, T30_PIN);
            s->timer_t3 = ms_to_samples(DEFAULT_TIMER_T3);
        }
        break;
    case T30_ERR:

        s->timer_t5 = 0;
        send_dcn(s);
        break;
    case T30_CRP:
        repeat_last_command(s);
        break;
    case T30_FNV:
        process_rx_fnv(s, msg, len);
        break;
    default:

        unexpected_final_frame(s, msg, len);
        break;
    }
}
