efreet_menu_filter_and_matches(Efreet_Menu_Filter_Op *op, Efreet_Menu_Desktop *md)
{
    Efreet_Menu_Filter_Op *child;
    Eina_List *l;
    char *t;

    if (op->categories)
    {
        if ((eina_list_count(op->categories) > 0) && !md->desktop->categories)
            return 0;

        EINA_LIST_FOREACH(op->categories, l, t)
        {
            if (!eina_list_search_unsorted(md->desktop->categories,
                                           EINA_COMPARE_CB(strcmp), t))
                return 0;
        }
    }

    if (op->filenames)
    {
        EINA_LIST_FOREACH(op->filenames, l, t)
        {
            if (t != md->id) return 0;
        }
    }

    if (op->filters)
    {
        EINA_LIST_FOREACH(op->filters, l, child)
        {
            if (!efreet_menu_filter_matches(child, md))
                return 0;
        }
    }

    return 1;
}
