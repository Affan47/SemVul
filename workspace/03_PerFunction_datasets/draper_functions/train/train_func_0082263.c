inmidi_programchange(int portno, int channel, int value)
{
    if (pgmin_sym->s_thing)
    {
        t_atom at[2];
        SETFLOAT(at, value + 1);
        SETFLOAT(at+1, (channel + (portno << 4) + 1));
        pd_list(pgmin_sym->s_thing, &s_list, 2, at);
    }
}
