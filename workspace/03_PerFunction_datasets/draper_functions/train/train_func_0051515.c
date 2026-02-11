gs_debug_c(int c)
{
    bool ret = gs_debug[c];


    c = gs_debug_flag_implied_by[c];
    if (c == 0)
        return ret;

    do {
        ret |= gs_debug[c];
    } while ((c = gs_debug_flag_implied_by[c]) != 0);
    return ret;
}
