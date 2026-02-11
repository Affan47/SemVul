populate_selection_list_on_scandb_cb(GBDATA *dummy, struct adawcbstruct *cbs)
{
    GBDATA *gb_key_data;
    gb_key_data = GB_search(cbs->gb_main, cbs->selector->change_key_path, GB_CREATE_CONTAINER);
    AWUSE(dummy);

    cbs->aws->clear_selection_list(cbs->id);

    if (cbs->add_pseudo_fields) {
        cbs->aws->insert_selection(cbs->id, PSEUDO_FIELD_ANY_FIELD, PSEUDO_FIELD_ANY_FIELD);
        cbs->aws->insert_selection(cbs->id, PSEUDO_FIELD_ALL_FIELDS, PSEUDO_FIELD_ALL_FIELDS);
    }

    for (GBDATA *gb_key = GB_entry(gb_key_data,CHANGEKEY); gb_key; gb_key = GB_nextEntry(gb_key)) {
        GBDATA *gb_key_type = GB_entry(gb_key,CHANGEKEY_TYPE);
        if ( !( ((long)cbs->def_filter) & (1<<GB_read_int(gb_key_type)))) continue;

        GBDATA *gb_key_name = GB_entry(gb_key,CHANGEKEY_NAME);
        if (!gb_key_name) continue;

        const char *name = GB_read_char_pntr(gb_key_name);
        if (!name) {
            fprintf(stderr, "WARNING: can't read key name (Reason: %s)", GB_await_error());
            name = "<unnamedKey?>";
        }

        long       *hiddenPtr = GBT_read_int(gb_key, CHANGEKEY_HIDDEN);
        const char *display   = 0;

        if (!hiddenPtr) {
            GB_ERROR error = GBT_write_int(gb_key, CHANGEKEY_HIDDEN, 0);
            if (error) {
                GB_warningf("WARNING: can't create " CHANGEKEY_HIDDEN " (Reason: %s)\n", error);
            }

            static long not_hidden = 0;;
            hiddenPtr              = &not_hidden;
        }

        if (*hiddenPtr) {
            if (cbs->include_hidden_fields) {
                display = GBS_global_string("[hidden] %s", name);
            }
        }
        else display = name;

        if (display) cbs->aws->insert_selection(cbs->id, display, name);
    }

    cbs->aws->insert_default_selection( cbs->id, "????", "----" );
    cbs->aws->update_selection_list( cbs->id );
}
