wstring_list_free(wstring_list_ty *wlp)
{
    size_t          j;

    for (j = 0; j < wlp->nitems; j++)
        wstr_free(wlp->item[j]);
    if (wlp->item)
        mem_free(wlp->item);
    wlp->nitems = 0;
    wlp->nitems_max = 0;
    wlp->item = 0;
}
