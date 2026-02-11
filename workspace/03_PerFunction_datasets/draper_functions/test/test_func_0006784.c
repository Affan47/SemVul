xconf_new_from_systemmenu()
{
    xconf *xc, *mxc, *tmp;
    GSList *w;
    GHashTable *ht;
    int i;
    const gchar * const * dirs;


    ht = g_hash_table_new(g_str_hash, g_str_equal);
    xc = xconf_new("systemmenu", NULL);
    for (i = 0; i < G_N_ELEMENTS(main_cats); i++)
    {
        mxc = xconf_new("menu", NULL);
        xconf_append(xc, mxc);

        tmp = xconf_new("name", main_cats[i].local_name ?
            main_cats[i].local_name : main_cats[i].name);
        xconf_append(mxc, tmp);

        tmp = xconf_new("icon", main_cats[i].icon);
        xconf_append(mxc, tmp);

        g_hash_table_insert(ht, main_cats[i].name, mxc);
    }


    for (dirs = g_get_system_data_dirs(); *dirs; dirs++)
        do_app_dir(ht, *dirs);
    do_app_dir(ht, g_get_user_data_dir());


retry:
    for (w = xc->sons; w; w = g_slist_next(w))
    {
        tmp = w->data;
        if (!xconf_find(tmp, "item", 0))
        {
            xconf_del(tmp, FALSE);
            goto retry;
        }
    }


    xc->sons = g_slist_sort(xc->sons, (GCompareFunc) xconf_cmp_names);
    for (w = xc->sons; w; w = g_slist_next(w))
    {
        tmp = w->data;
        tmp->sons = g_slist_sort(tmp->sons, (GCompareFunc) xconf_cmp_names);
    }

    g_hash_table_destroy(ht);

    return xc;
}
