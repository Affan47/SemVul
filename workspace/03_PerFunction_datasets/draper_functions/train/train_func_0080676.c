skip_tail(Octstr **os, int delimiter)
{
    long delimiter_pos;

    if ((delimiter_pos = octstr_search_char(*os, delimiter, 0)) == -1)
        return 0;

    octstr_delete(*os, delimiter_pos, octstr_len(*os) - delimiter_pos);

    return 1;
}
