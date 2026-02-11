string_list_intersect(const string_list_ty *wl1, const string_list_ty *wl2)
{
    size_t          j;

    if (wl1->nstrings > wl2->nstrings)
    {
        for (j = 0; j < wl2->nstrings; j++)
            if (string_list_member(wl1, wl2->string[j]))
                return 1;
    }
    else
    {
        for (j = 0; j < wl1->nstrings; j++)
            if (string_list_member(wl2, wl1->string[j]))
                return 1;
    }
    return 0;
}
