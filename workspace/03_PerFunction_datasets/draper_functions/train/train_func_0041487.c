ste_next(TermEnum *te)
{
    TermInfo *ti;
    InStream *is = STE(te)->is;

    STE(te)->pos++;
    if (STE(te)->pos >= STE(te)->size) {
        te->curr_term[0] = '\0';
        te->curr_term_len = 0;
        return NULL;
    }

    memcpy(te->prev_term, te->curr_term, te->curr_term_len + 1);
    te->curr_term_len = term_read(te->curr_term, is);

    ti = &(te->curr_ti);
    ti->doc_freq = is_read_vint(is);
    ti->frq_ptr += is_read_voff_t(is);
    ti->prx_ptr += is_read_voff_t(is);
    if (ti->doc_freq >= STE(te)->skip_interval) {
        ti->skip_offset = is_read_voff_t(is);
    }

    return te->curr_term;
}
