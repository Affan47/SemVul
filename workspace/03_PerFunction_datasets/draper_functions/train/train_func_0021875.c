efreet_desktop_get(const char *file)
{
    Efreet_Desktop *desktop;

    EINA_SAFETY_ON_NULL_RETURN_VAL(file, NULL);

    desktop = efreet_desktop_new(file);
    if (!desktop) return NULL;


    if (!desktop->eet)
    {


        Efreet_Desktop_Type_Info *info;

        info = eina_list_nth(efreet_desktop_types, desktop->type);
        if (info && (
                info->id == EFREET_DESKTOP_TYPE_APPLICATION ||
                info->id == EFREET_DESKTOP_TYPE_LINK ||
                info->id == EFREET_DESKTOP_TYPE_DIRECTORY
                ))
            efreet_cache_desktop_add(desktop);
    }

    return desktop;
}
