get_tvpe(TermVector *tv, char **terms, int t_cnt, int offset)
{
    TVPosEnum *tvpe = NULL;
    if (t_cnt == 1) {
        TVTerm *tv_term = tv_get_tv_term(tv, terms[0]);
        if (tv_term) {
            tvpe = tvpe_new(tv_term->positions, tv_term->freq, offset);
        }
    }
    else {
        tvpe = tvpe_new_merge(terms, t_cnt, tv, offset);
    }
    return tvpe;
}
