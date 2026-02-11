deleter_find_deletable_files(Deleter *dlr)
{

    int i;
    SegmentInfos *sis = dlr->sis;
    Store *store = dlr->store;
    struct DelFilesArg dfa;
    HashTable *current = dfa.current
                       = h_new_str((free_ft)NULL, (free_ft)si_deref);
    dfa.dlr = dlr;

    for(i = 0; i < sis->size; i++) {
        SegmentInfo *si = (SegmentInfo *)sis->segs[i];
        REF(si);
        h_set(current, si->name, si);
    }


    sis_curr_seg_file_name(dfa.curr_seg_file_name, store);
    file_name_filter_init();

    store->each(store, &deleter_find_deletable_files_i, &dfa);
    h_destroy(dfa.current);
}
