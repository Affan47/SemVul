modem_echo_can_update(modem_echo_can_state_t *ec, int16_t tx, int16_t rx)
{
    int32_t echo_value;
    int clean_rx;
    int shift;
    int i;
    int offset1;
    int offset2;


    echo_value = fir16(&ec->fir_state, tx);


    clean_rx = rx - echo_value;

    if (ec->adapt)
    {


        ec->tx_power += ((tx*tx - ec->tx_power) >> 5);

        shift = 1;

        offset2 = ec->curr_pos;
        offset1 = ec->taps - offset2;
        for (i = ec->taps - 1;  i >= offset1;  i--)
        {


            ec->fir_taps32[i] -= (ec->fir_taps32[i] >> 23);
            ec->fir_taps32[i] += (ec->fir_state.history[i - offset1]*clean_rx) >> shift;
            ec->fir_taps16[i] = (int16_t) (ec->fir_taps32[i] >> 15);
        }
        for (  ;  i >= 0;  i--)
        {
            ec->fir_taps32[i] -= (ec->fir_taps32[i] >> 23);
            ec->fir_taps32[i] += (ec->fir_state.history[i + offset2]*clean_rx) >> shift;
            ec->fir_taps16[i] = (int16_t) (ec->fir_taps32[i] >> 15);
        }
    }


    if (ec->curr_pos <= 0)
        ec->curr_pos = ec->taps;
    ec->curr_pos--;
    return  (int16_t) clean_rx;
}
