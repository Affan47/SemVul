ste_scan_to(TermEnum *te, const char *term)
{
    SegmentFieldIndex *sfi = STE(te)->sfi;
    SegmentTermIndex *sti
        = (SegmentTermIndex *)h_get_int(sfi->field_dict, te->field_num);
    if (sti && sti->size > 0) {
        SFI_ENSURE_INDEX_IS_READ(sfi, sti);
        if (term[0] == '\0') {
            ste_index_seek(te, sti, 0);
            return ste_next(te);;
        }

        if (STE(te)->pos < STE(te)->size && strcmp(te->curr_term, term) <= 0) {
            int enum_offset = (int)(STE(te)->pos / sfi->index_interval) + 1;


            if (sti->index_cnt == enum_offset ||
                strcmp(term, sti->index_terms[enum_offset]) < 0) {
                return te_skip_to(te, term);
            }
        }
        ste_index_seek(te, sti, sti_get_index_offset(sti, term));
        return te_skip_to(te, term);
    }
    else {
        return NULL;
    }
}
