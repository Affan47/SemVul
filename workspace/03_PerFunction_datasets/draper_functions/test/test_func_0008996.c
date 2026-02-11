efreet_menu_handle_merge_dir(Efreet_Menu_Internal *parent, Efreet_Xml *xml)
{
    const char *path;
    int ret;

    if (!parent || !xml || !xml->text) return 0;

    path = efreet_menu_path_get(parent, xml->text);
    if (!path) return 1;
    if (!ecore_file_exists(path))
    {
        eina_stringshare_del(path);
        return 1;
    }

    ret = efreet_menu_merge_dir(parent, xml, path);
    eina_stringshare_del(path);

    return ret;
}
