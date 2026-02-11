gnc_g_list_cut(GList **list, GList *cut_point)
{
    if (list == NULL || *list == NULL)
        return;


    if (cut_point->prev == NULL)
    {
        *list = NULL;
        return;
    }

    cut_point->prev->next = NULL;
    cut_point->prev = NULL;
}
