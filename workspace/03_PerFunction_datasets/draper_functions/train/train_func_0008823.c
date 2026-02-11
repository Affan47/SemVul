hostrange_hn_within(hostrange_t hr, hostname_t hn)
{
    if (hr->singlehost) {


        if (strcmp (hn->hostname, hr->prefix) == 0)
            return 1;
        else
            return 0;
    }


    if (!hostname_suffix_is_valid (hn))
        return 0;


    if (strcmp(hr->prefix, hn->prefix) != 0)
        return 0;


    if (hn->num <= hr->hi && hn->num >= hr->lo) {
        int width = hostname_suffix_width(hn);
        int num = hn->num;
        return (_width_equiv(hr->lo, &hr->width, num, &width));
    }

    return 0;
}
