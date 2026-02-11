descramble(v17_rx_state_t *s, int in_bit)
{
    int out_bit;

    out_bit = (in_bit ^ (s->scramble_reg >> 17) ^ (s->scramble_reg >> 22)) & 1;
    s->scramble_reg <<= 1;
    if (s->training_stage > TRAINING_STAGE_NORMAL_OPERATION  &&  s->training_stage < TRAINING_STAGE_TCM_WINDUP)
        s->scramble_reg |= out_bit;
    else
        s->scramble_reg |= (in_bit & 1);
    return out_bit;
}
