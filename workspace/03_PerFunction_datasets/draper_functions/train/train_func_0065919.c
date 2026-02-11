init_alignment() {
    GB_transaction dummy(GLOBAL_gb_main);

    alignment_name = GBT_get_default_alignment(GLOBAL_gb_main);
    alignment_type = GBT_get_alignment_type(GLOBAL_gb_main,alignment_name);
    if (alignment_type==GB_AT_UNKNOWN) {
        aw_popup_exit("You have to select a valid alignment before you can start ARB_EDIT4");
    }

    GBDATA *gb_alignment = GBT_get_alignment(GLOBAL_gb_main, alignment_name);
    if (!gb_alignment) aw_popup_exit("You can't edit without an existing alignment");

    GBDATA *gb_alignment_len = GB_search(gb_alignment,"alignment_len",GB_FIND);
    int alignment_length = GB_read_int(gb_alignment_len);
    MAXSEQUENCECHARACTERLENGTH = alignment_length;

    GB_add_callback(gb_alignment_len, (GB_CB_TYPE)GB_CB_CHANGED, (GB_CB)ED4_alignment_length_changed, 0);

    aw_root->awar_string(AWAR_EDITOR_ALIGNMENT, alignment_name);

    return ED4_R_OK;
}
