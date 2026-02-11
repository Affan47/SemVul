probe_is_ok(char *probe, int probe_len, char first_c, char second_c)
{
    int i;
    if (probe_len < 2 || probe[0] != first_c || probe[1] != second_c)
        return 0;
    for (i = 2; i < probe_len; i++)
        if (probe[i] < PT_A || probe[i] > PT_T)
            return 0;
    return 1;
}
