open_default(const char *default_name, bool create_if_missing)
{
    if (!create_if_missing) {
        const char *home   = GB_getenvHOME();
        char       *buffer = (char *)GB_calloc(sizeof(char),strlen(home)+ strlen(default_name) + 2);

        sprintf(buffer,"%s/%s", home, default_name);

        struct stat st;
        bool        found = stat(buffer, &st) == 0;

        free(buffer);

        if (!found) return 0;
    }

#if defined(DEVEL_RALF)
#warning gb_default is never closed

#endif

    GBDATA *gb_default = GB_open(default_name, "rwcD");

    if (gb_default) {
        GB_no_transaction(gb_default);

        GBDATA *gb_tmp = GB_search(gb_default, "tmp", GB_CREATE_CONTAINER);
        GB_set_temporary(gb_tmp);
#if defined(DEBUG)
        AWT_announce_db_to_browser(gb_default, GBS_global_string("Properties (%s)", default_name));
#endif
    }
    else {
        GB_ERROR    error           = GB_await_error();
        const char *shown_name      = strrchr(default_name, '/');
        if (!shown_name) shown_name = default_name;

        GBK_terminatef("Error loading properties '%s': %s", shown_name, error);
    }
    return (AW_default) gb_default;
}
