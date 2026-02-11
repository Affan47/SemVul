efreet_menu_file_set(const char *file)
{
    IF_RELEASE(efreet_menu_file);
    efreet_menu_file = NULL;
    if (file) efreet_menu_file = eina_stringshare_add(file);
}
