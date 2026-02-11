process_state_d_tcf(t30_state_t *s, const uint8_t *msg, int len)
{

    switch (msg[2] & 0xFE)
    {
    case T30_DCN:
        s->current_status = T30_ERR_TX_BADDCS;
        disconnect(s);
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
