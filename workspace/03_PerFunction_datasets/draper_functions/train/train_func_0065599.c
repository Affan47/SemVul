sm_append_postings(SegmentMerger *sm, SegmentMergeInfo **matches,
                              const int match_size)
{
    int i;
    int last_doc = 0, base, doc, doc_code, freq;
    int skip_interval = sm->config->skip_interval;
    int *doc_map = NULL;
    int df = 0;
    TermDocEnum *tde;
    SegmentMergeInfo *smi;
    SkipBuffer *skip_buf = sm->skip_buf;
    skip_buf_reset(skip_buf);

    for (i = 0; i < match_size; i++) {
        smi = matches[i];
        base = smi->base;
        doc_map = smi->doc_map;
        tde = smi->tde;
        stpe_seek_ti(STDE(tde), &smi->te->curr_ti);


        while (stde_next(tde)) {
            doc = stde_doc_num(tde);
            if (NULL != doc_map) {
                doc = doc_map[doc];
            }
            doc += base;

#ifdef DEBUG
            if (doc && doc <= last_doc) {
                RAISE(STATE_ERROR, "Docs not ordered, %d < %d", doc, last_doc);
            }
#endif
            df++;

            if (0 == (df % skip_interval)) {
                skip_buf_add(skip_buf, last_doc);
            }

            doc_code = (doc - last_doc) << 1;
            last_doc = doc;

            freq = stde_freq(tde);
            if (freq == 1) {
                os_write_vint(sm->frq_out, doc_code | 1);
            }
            else {
                os_write_vint(sm->frq_out, doc_code);
                os_write_vint(sm->frq_out, freq);
            }


            is2os_copy_vints(STDE(tde)->prx_in, sm->prx_out, freq);
        }
    }
    return df;
}
