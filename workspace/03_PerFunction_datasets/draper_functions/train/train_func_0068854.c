ci_decode(v8_state_t *s)
{
    if ((s->rx_data[0] & 0x1F) == 0x01)
        process_call_function(s, &s->rx_data[0]);
}
