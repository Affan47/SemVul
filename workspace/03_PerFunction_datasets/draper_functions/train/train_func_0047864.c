efreet_mime_type_icon_get(const char *mime, const char *theme, unsigned int size)
{
    const char *icon = NULL;
    char *data;
    Eina_List *icons  = NULL;
    const char *env = NULL;
    char *p = NULL, *pp = NULL, *ppp = NULL;
    char buf[PATH_MAX];
    const char *cache;

    EINA_SAFETY_ON_NULL_RETURN_VAL(mime, NULL);
    EINA_SAFETY_ON_NULL_RETURN_VAL(theme, NULL);

    mime = eina_stringshare_add(mime);
    theme = eina_stringshare_add(theme);
    cache = efreet_mime_icon_entry_find(mime, theme, size);
    if (cache)
    {
        eina_stringshare_del(mime);
        eina_stringshare_del(theme);
        return cache;
    }


    p = strdup(mime);
    pp = p;
    while (*pp)
    {
        if (*pp == '/') *pp = '-';
        pp++;
    }
    icons = eina_list_append(icons, p);


    if ((env = efreet_desktop_environment_get()))
    {
        snprintf(buf, sizeof(buf), "%s-mime-%s", env, p);
        icons = eina_list_append(icons, strdup(buf));

        snprintf(buf, sizeof(buf), "%s-%s", env, p);
        icons = eina_list_append(icons, strdup(buf));
    }


    snprintf(buf, sizeof(buf), "mime-%s", p);
    icons = eina_list_append(icons, strdup(buf));


    pp = strdup(p);
    while ((ppp = strrchr(pp, '-')))
    {
        *ppp = '\0';

        snprintf(buf, sizeof(buf), "%s-x-generic", pp);
        icons = eina_list_append(icons, strdup(buf));

        snprintf(buf, sizeof(buf), "%s-generic", pp);
        icons = eina_list_append(icons, strdup(buf));

        snprintf(buf, sizeof(buf), "%s", pp);
        icons = eina_list_append(icons, strdup(buf));
    }
    FREE(pp);


    icon = efreet_icon_list_find(theme, icons, size);
    while (icons)
    {
        data = eina_list_data_get(icons);
        free(data);
        icons = eina_list_remove_list(icons, icons);
    }

    efreet_mime_icon_entry_add(mime, eina_stringshare_add(icon), theme, size);

    return icon;
}
