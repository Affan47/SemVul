cheapest_sequence(void)
{

    char *seq;
    size_t p;
    int i, min_i;
    float min;


    seq = (char *) CALLOC((unsigned int) prof_len + 1, sizeof(char));
    if (seq == 0)
        ali_fatal_error("Out of memory");

    for (p = 0; p < prof_len; p++) {
        min = (*sub_costs)[p][0];
        min_i = 0;
        for (i = 1; i < 5; i++) {
            if (min > (*sub_costs)[p][i]) {
                min = (*sub_costs)[p][i];
                min_i = i;
            }
            else {
                if (min == (*sub_costs)[p][i])
                    min_i = -1;
            }
        }
        if (min_i >= 0)
            seq[p] = ali_number_to_base(min_i);
        else {
            if (min > 0)
                seq[p] = '*';
            else
                seq[p] = '.';
        }
    }
    seq[prof_len] = '\0';

    return seq;
}
