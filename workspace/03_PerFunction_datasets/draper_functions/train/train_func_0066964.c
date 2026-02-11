script_handler_search(spif_charptr_t *params)
{
    static char *search = NULL;

    if (params && *params) {
        if (search) {
            FREE(search);
        }
        search = STRDUP(*params);
    }
    if ((menu_dialog(NULL, "Enter Search Term:", TERM_WINDOW_GET_REPORTED_COLS(), &search, NULL)) != -2) {
        scr_search_scrollback(search);
    }
}
