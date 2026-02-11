efreet_cache_icon_theme_free(Efreet_Icon_Theme *theme)
{
    void *data;

    if (!theme) return;
    if (theme == NON_EXISTING) return;

    eina_list_free(theme->paths);
    eina_list_free(theme->inherits);
    EINA_LIST_FREE(theme->directories, data)
        free(data);

    free(theme);
}
