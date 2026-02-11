wstring_list_member(wstring_list_ty *wlp, wstring_ty *w)
{
    size_t          j;

    for (j = 0; j < wlp->nitems; j++)
        if (wstr_equal(wlp->item[j], w))
            return 1;
    return 0;
}
