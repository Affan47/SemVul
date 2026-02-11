createSelectionList(GBDATA *gb_main,AW_window *aws, const char *awarName){

#ifdef DEBUG
    static bool ran=false;
    gb_assert(!ran);
    ran=true;
#endif

    GBDATA *gb_presets;
    AW_root *aw_root  = aws->get_root();
    char    *ali_type = aw_root->awar(AWAR_CON_SEQUENCE_TYPE)->read_string();
    ali_type          = GBS_global_string_copy("%s=", ali_type);

    db_alignment_list = aws->create_selection_list(awarName,0,"",10,20);

    conAlignStruct *cas = 0;
    cas          = new conAlignStruct;
    cas->aws     = aws;
    cas->gb_main = gb_main;
    cas->db_id   = db_alignment_list;
    cas->seqType  = 0; if (ali_type) cas->seqType = strdup(ali_type);

    createSelectionList_callBack(cas);

    GB_push_transaction(gb_main);
    gb_presets = GB_search(gb_main,"presets",GB_CREATE_CONTAINER);
    GB_add_callback(gb_presets, GB_CB_CHANGED, createSelectionList_callBack_gb, (int *)cas);
    GB_pop_transaction(gb_main);

    free(ali_type);
    return cas;

}
