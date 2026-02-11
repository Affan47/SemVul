timer_t4_expired(t30_state_t *s)
{


    span_log(&s->logging, SPAN_LOG_FLOW, "T4 expired in phase %s, state %d\n", phase_names[s->phase], s->state);
    if (++s->retries > MAX_MESSAGE_TRIES)
    {
        switch (s->state)
        {
        case T30_STATE_D_POST_TCF:

            s->current_status = T30_ERR_TX_PHBDEAD;
            break;
        case T30_STATE_II_Q:
        case T30_STATE_IV_PPS_NULL:
        case T30_STATE_IV_PPS_Q:

            s->current_status = T30_ERR_TX_PHDDEAD;
            break;
        default:

            s->current_status = T30_ERR_RETRYDCN;
            break;
        }
        send_dcn(s);
        return;
    }


    repeat_last_command(s);
}
