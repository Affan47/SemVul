async_tx_get_bit(void *user_data)
{
    async_tx_state_t *s;
    int bit;

    s = (async_tx_state_t *) user_data;
    if (s->bitpos == 0)
    {
        if ((s->byte_in_progress = s->get_byte(s->user_data)) < 0)
        {

            bit = PUTBIT_END_OF_DATA;
        }
        else
        {

            bit = 0;
            s->parity_bit = 0;
            s->bitpos++;
        }
    }
    else if (s->bitpos <= s->data_bits)
    {
        bit = s->byte_in_progress & 1;
        s->byte_in_progress >>= 1;
        s->parity_bit ^= bit;
        s->bitpos++;
    }
    else if (s->parity  &&  s->bitpos == s->data_bits + 1)
    {
        if (s->parity == ASYNC_PARITY_ODD)
            s->parity_bit ^= 1;
        bit = s->parity_bit;
        s->bitpos++;
    }
    else
    {

        bit = 1;
        if (++s->bitpos > s->data_bits + s->stop_bits)
            s->bitpos = 0;
    }
    return bit;
}
