tv_tde_seek(TermDocEnum *tde, int field_num, const char *term)
{
    TVTermDocEnum *tv_tde = TV_TDE(tde);
    TVTerm *tv_term = tv_get_tv_term(tv_tde->tv, term);
    (void)field_num;
    if (tv_term) {
        tv_tde->doc = -1;
        tv_tde->index = 0;
        tv_tde->freq = tv_term->freq;
        tv_tde->positions = tv_term->positions;
    }
    else {
        tv_tde->doc = INT_MAX;
    }
}
