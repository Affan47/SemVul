v27ter_tx_restart(v27ter_tx_state_t *s, int bit_rate, int tep)
{
    if (bit_rate != 4800  &&  bit_rate != 2400)
        return -1;
    s->bit_rate = bit_rate;
#if defined(SPANDSP_USE_FIXED_POINT)
    memset(s->rrc_filter, 0, sizeof(s->rrc_filter));
#else
    cvec_zerof(s->rrc_filter, sizeof(s->rrc_filter)/sizeof(s->rrc_filter[0]));
#endif
    s->rrc_filter_step = 0;
    s->scramble_reg = 0x3C;
    s->scrambler_pattern_count = 0;
    s->in_training = TRUE;
    s->training_step = (tep)  ?  V27TER_TRAINING_SEG_1  :  V27TER_TRAINING_SEG_2;
    s->carrier_phase = 0;
    s->baud_phase = 0;
    s->constellation_state = 0;
    s->current_get_bit = fake_get_bit;
    return 0;
}
