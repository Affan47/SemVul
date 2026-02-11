async_tx_init(async_tx_state_t *s,
                                int data_bits,
                                int parity,
                                int stop_bits,
                                int use_v14,
                                get_byte_func_t get_byte,
                                void *user_data)
{
    if (s == NULL)
    {
        if ((s = (async_tx_state_t *) malloc(sizeof(*s))) == NULL)
            return NULL;
    }


    s->data_bits = data_bits;
    s->parity = parity;
    s->stop_bits = stop_bits;
    if (parity != ASYNC_PARITY_NONE)
        s->stop_bits++;

    s->get_byte = get_byte;
    s->user_data = user_data;

    s->byte_in_progress = 0;
    s->bitpos = 0;
    s->parity_bit = 0;
    return s;
}
