rx_special_condition(hdlc_rx_state_t *s, int condition)
{

    switch (condition)
    {
    case PUTBIT_CARRIER_UP:
    case PUTBIT_TRAINING_SUCCEEDED:

        s->raw_bit_stream = 0;
        s->len = 0;
        s->num_bits = 0;
        s->flags_seen = 0;
        s->framing_ok_announced = FALSE;

    case PUTBIT_TRAINING_IN_PROGRESS:
    case PUTBIT_TRAINING_FAILED:
    case PUTBIT_CARRIER_DOWN:
    case PUTBIT_END_OF_DATA:
        s->frame_handler(s->user_data, NULL, condition, TRUE);
        break;
    default:

        break;
    }
}
