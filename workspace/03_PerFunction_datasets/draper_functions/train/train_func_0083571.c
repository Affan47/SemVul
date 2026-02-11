check_changed(Efreet_Cache_Icon_Theme *theme)
{
    Eina_List *l;
    const char *name;

    if (!theme) return EINA_FALSE;

    if (theme->changed) return EINA_TRUE;
    if (theme->theme.inherits)
    {
        EINA_LIST_FOREACH(theme->theme.inherits, l, name)
        {
            Efreet_Cache_Icon_Theme *inherit;

            inherit = eina_hash_find(icon_themes, name);
            if (!inherit)
                INF("Theme `%s` not found for `%s`.",
                        name, theme->theme.name.internal);
            if (check_changed(inherit)) return EINA_TRUE;
        }
    }
    else if (strcmp(theme->theme.name.internal, "hicolor"))
    {
        theme = eina_hash_find(icon_themes, "hicolor");
        if (check_changed(theme)) return EINA_TRUE;
    }
    return EINA_FALSE;
}
