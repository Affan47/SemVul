efreet_menu_process_dirs(Efreet_Menu_Internal *internal)
{
    Eina_List *l;


    if (!efreet_menu_app_dirs_process(internal))
        return 0;


    if (!efreet_menu_directory_dirs_process(internal))
        return 0;

    if (internal->sub_menus)
    {
        Efreet_Menu_Internal *sub_internal;

        EINA_LIST_FOREACH(internal->sub_menus, l, sub_internal)
        {
            sub_internal->parent = internal;
            efreet_menu_process_dirs(sub_internal);
        }
    }

    return 1;
}
