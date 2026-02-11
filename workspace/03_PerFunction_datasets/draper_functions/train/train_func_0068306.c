get_O_dtp_list(int target_mt,
               int array_entry,
               DtScheInfo *dt_sche)
{
    List *ret = NULL;
    Array_def_use_table_semnode *O;
    Block *bpt;

    bpt = dt_sche->block[target_mt];
    O = search_array_du_from_entry(get_array_OuterLiveOut(bpt), array_entry, KIND_ARRAY);
    if (O != NULL) {
        O = make_one_estimated_region_aduts(O, bpt->module);

        ret = list_concat(ret,
                          get_dtp_list(O, DTU_STORE,
                                       target_mt, -1, NULL, dt_sche));
        free_array_def_use_table_semnode(O);
    }
    return ret;
}
