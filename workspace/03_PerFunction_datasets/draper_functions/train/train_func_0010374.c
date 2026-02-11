efreet_menu_desktop_insert(Efreet_Menu *menu, Efreet_Desktop *desktop, int pos)
{
    Efreet_Menu *entry;
    const char *id;

    EINA_SAFETY_ON_NULL_RETURN_VAL(menu, 0);
    EINA_SAFETY_ON_NULL_RETURN_VAL(desktop, 0);

    id = efreet_util_path_to_file_id(desktop->orig_path);
    if (!id) return 0;

    entry = efreet_menu_entry_new();
    entry->type = EFREET_MENU_ENTRY_DESKTOP;
    entry->id = eina_stringshare_add(id);
    entry->name = eina_stringshare_add(desktop->name);
    if (desktop->icon) entry->icon = eina_stringshare_add(desktop->icon);
    efreet_desktop_ref(desktop);
    entry->desktop = desktop;

    if (pos < 0 || (unsigned int)pos >= eina_list_count(menu->entries))
        menu->entries = eina_list_append(menu->entries, entry);
    else
    {
        menu->entries = eina_list_append_relative(menu->entries, entry,
                                                  eina_list_nth(menu->entries, pos));
    }
    return 1;
}
