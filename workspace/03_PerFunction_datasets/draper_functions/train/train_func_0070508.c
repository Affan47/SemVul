sm_merge_norms(SegmentMerger *sm)
{
    SegmentInfo *si;
    int i, j, k;
    Store *store;
    uchar byte;
    FieldInfo *fi;
    OutStream *os;
    InStream *is;
    char file_name[SEGMENT_NAME_MAX_LENGTH];
    SegmentMergeInfo *smi;
    const int seg_cnt = sm->seg_cnt;
    for (i = sm->fis->size - 1; i >= 0; i--) {
        fi = sm->fis->fields[i];
        if (fi_has_norms(fi))  {
            si = sm->si;
            si_advance_norm_gen(si, i);
            si_norm_file_name(si, file_name, i);
            os = sm->store->new_output(sm->store, file_name);
            for (j = 0; j < seg_cnt; j++) {
                smi = sm->smis[j];
                si = smi->si;
                if (si_norm_file_name(si, file_name, i)) {
                    const int max_doc = smi->max_doc;
                    BitVector *deleted_docs =  smi->deleted_docs;
                    store = (si->use_compound_file && si->norm_gens[i])
                             ? smi->orig_store : smi->store;
                    is = store->open_input(store, file_name);
                    if (deleted_docs) {
                        for (k = 0; k < max_doc; k++) {
                            byte = is_read_byte(is);
                            if (!bv_get(deleted_docs, k)) {
                                os_write_byte(os, byte);
                            }
                        }
                    }
                    else {
                        is2os_copy_bytes(is, os, max_doc);
                    }
                    is_close(is);
                }
                else {
                    const int doc_cnt = smi->doc_cnt;
                    for (k = 0; k < doc_cnt; k++) {
                        os_write_byte(os, '\0');
                    }
                }
            }
            os_close(os);
        }
    }
}
