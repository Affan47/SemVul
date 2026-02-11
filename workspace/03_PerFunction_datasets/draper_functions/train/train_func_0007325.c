t38_terminal_set_fill_bit_removal(t38_terminal_state_t *s, int remove)
{
    if (remove)
        s->t38_fe.iaf |= T30_IAF_MODE_NO_FILL_BITS;
    else
        s->t38_fe.iaf &= ~T30_IAF_MODE_NO_FILL_BITS;
    t30_set_iaf_mode(&(s->t30), s->t38_fe.iaf);
}
