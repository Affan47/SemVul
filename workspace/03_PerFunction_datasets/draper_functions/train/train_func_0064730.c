awt_create_selection_list_on_ad_cb(GBDATA *, struct adawcbstruct *cbs) {
    cbs->aws->clear_selection_list(cbs->id);

    for (GBDATA * gb_alignment = GB_search(cbs->gb_main, "presets/alignment", GB_FIND);
         gb_alignment;
         gb_alignment = GB_nextEntry(gb_alignment))
    {
        char *alignment_type = GBT_read_string(gb_alignment, "alignment_type");
        char *alignment_name = GBT_read_string(gb_alignment, "alignment_name");
        char *str            = GBS_string_eval(alignment_type, cbs->comm, 0);

        if (!*str) {
            cbs->aws->insert_selection(cbs->id, alignment_name, alignment_name);
        }
        free(str);
        free(alignment_type);
        free(alignment_name);
    }
    cbs->aws->insert_default_selection(cbs->id, "????", "????");
    cbs->aws->update_selection_list(cbs->id);
}
