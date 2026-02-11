sti_ensure_index_is_read(SegmentTermIndex *sti,
                                     TermEnum *index_te)
{
    if (NULL == sti->index_terms) {
        int i;
        int index_cnt = sti->index_cnt;
        off_t index_ptr = 0;
        ste_reset(index_te);
        is_seek(STE(index_te)->is, sti->index_ptr);
        STE(index_te)->size = sti->index_cnt;

        sti->index_terms = ALLOC_N(char *, index_cnt);
        sti->index_term_lens = ALLOC_N(int, index_cnt);
        sti->index_term_infos = ALLOC_N(TermInfo, index_cnt);
        sti->index_ptrs = ALLOC_N(off_t, index_cnt);

        for (i = 0; NULL != ste_next(index_te); i++) {
#ifdef DEBUG
            if (i >= index_cnt) {
                RAISE(FERRET_ERROR, "index term enum read too many terms");
            }
#endif
            sti->index_terms[i] = te_get_term(index_te);
            sti->index_term_lens[i] = index_te->curr_term_len;
            sti->index_term_infos[i] = index_te->curr_ti;
            index_ptr += is_read_voff_t(STE(index_te)->is);
            sti->index_ptrs[i] = index_ptr;
        }
    }
}
