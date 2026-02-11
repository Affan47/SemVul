awt_selection_list_rescan(GBDATA *gb_main, long bitfilter, awt_rescan_mode mode) {
    GB_push_transaction(gb_main);
    char   **names;
    char   **name;
    GBDATA  *gb_species_data = GB_search(gb_main,"species_data",GB_CREATE_CONTAINER);

    names = GBT_scan_db(gb_species_data, 0);

    if (mode & AWT_RS_DELETE_UNUSED_FIELDS) awt_delete_unused_changekeys(gb_main, const_cast<const char **>(names), CHANGE_KEY_PATH);
    if (mode & AWT_RS_SHOW_ALL) awt_show_all_changekeys(gb_main, CHANGE_KEY_PATH);

    if (mode & AWT_RS_SCAN_UNKNOWN_FIELDS) {
        GBT_add_new_changekey(gb_main,"name",GB_STRING);
        GBT_add_new_changekey(gb_main,"acc",GB_STRING);
        GBT_add_new_changekey(gb_main,"full_name",GB_STRING);
        GBT_add_new_changekey(gb_main,"group_name",GB_STRING);
        GBT_add_new_changekey(gb_main,"tmp",GB_STRING);

        for (name = names; *name; name++) {
            if ( (1<<(**name)) & bitfilter ) {
                if (!is_in_reserved_path((*name)+1)) {
                    GBT_add_new_changekey(gb_main,(*name)+1,(int)*name[0]);
                }
            }
        }
    }

    GBT_free_names(names);
    GB_pop_transaction(gb_main);
}
