efreet_menu_layout_menu(Efreet_Menu_Internal *internal)
{
    Efreet_Menu *entry;
    Eina_List *layout = NULL;
    Eina_List *l;

    if (internal->parent)
    {

        if (internal->show_empty == -1)    internal->show_empty = internal->parent->show_empty;
        if (internal->in_line == -1)       internal->in_line = internal->parent->in_line;
        if (internal->inline_limit == -1)  internal->inline_limit = internal->parent->inline_limit;
        if (internal->inline_header == -1) internal->inline_header = internal->parent->inline_header;
        if (internal->inline_alias == -1)  internal->inline_alias = internal->parent->inline_alias;
    }

    if (internal->layout)
        layout = internal->layout;

    else if (internal->parent)
    {
        Efreet_Menu_Internal *parent;
        parent = internal->parent;
        do
        {
            layout = parent->default_layout;
            parent = parent->parent;
        } while (!layout && parent);
    }


    entry = efreet_menu_entry_new();
    entry->type = EFREET_MENU_ENTRY_MENU;
    entry->id = eina_stringshare_add(internal->name.internal);
    entry->name = eina_stringshare_add(internal->name.name);
    if (internal->directory)
    {
        entry->icon = eina_stringshare_add(internal->directory->icon);
        efreet_desktop_ref(internal->directory);
        entry->desktop = internal->directory;
    }
    entry->entries = NULL;

#if 1
    if (internal->sub_menus)
    {
        internal->sub_menus = eina_list_sort(internal->sub_menus,
                                             0,
                                             EINA_COMPARE_CB(efreet_menu_cb_menu_compare));
    }
#endif

    if (layout)
    {
        Efreet_Menu_Layout *lay;

        EINA_LIST_FOREACH(layout, l, lay)
            efreet_menu_layout_entries_get(entry, internal, lay);
    }
    else
    {

        if (internal->sub_menus)
        {
            Efreet_Menu_Internal *sub;

            EINA_LIST_FOREACH(internal->sub_menus, l, sub)
            {
                Efreet_Menu *sub_entry;
                if ((sub->directory && sub->directory->no_display) || sub->deleted) continue;
                sub_entry = efreet_menu_layout_menu(sub);

                if (!sub_entry->entries)
                {
                    efreet_menu_free(sub_entry);
                    continue;
                }
                entry->entries = eina_list_append(entry->entries, sub_entry);
            }
        }

        if (internal->applications)
        {
            Efreet_Menu_Desktop *md;

            EINA_LIST_FOREACH(internal->applications, l, md)
            {
                Efreet_Menu *sub_entry;
                sub_entry = efreet_menu_layout_desktop(md);
                entry->entries = eina_list_append(entry->entries, sub_entry);
            }
        }
    }


    return entry;
}
