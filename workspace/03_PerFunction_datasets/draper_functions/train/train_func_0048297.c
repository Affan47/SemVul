efreet_menu_process_app_pool(Eina_List *pool, Eina_List *applications,
                                Eina_Hash *matches, Efreet_Menu_Filter *filter,
                                unsigned int only_unallocated)
{
    Efreet_Menu_Desktop *md;
    Eina_List *l;

    EINA_LIST_FOREACH(pool, l, md)
    {
        if (eina_hash_find(matches, md->id)) continue;
        if (only_unallocated && md->allocated) continue;
        if (efreet_menu_filter_matches(filter->op, md))
        {
            applications = eina_list_append(applications, md);
            eina_hash_direct_add(matches, (void *)md->id, md);
            md->allocated = 1;
        }
    }
    return applications;
}
