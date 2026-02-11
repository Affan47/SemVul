r_verb_suffix(struct SN_env * z) {
    int among_var;
    {   int mlimit;
        int m1 = z->l - z->c; (void)m1;
        if (z->c < z->I[0]) return 0;
        z->c = z->I[0];
        mlimit = z->lb; z->lb = z->c;
        z->c = z->l - m1;
        z->ket = z->c;
        among_var = find_among_b(z, a_4, 94);
        if (!(among_var)) { z->lb = mlimit; return 0; }
        z->bra = z->c;
        switch(among_var) {
            case 0: { z->lb = mlimit; return 0; }
            case 1:
                {   int m2 = z->l - z->c; (void)m2;
                    if (out_grouping_b_U(z, g_v, 97, 259, 0)) goto lab1;
                    goto lab0;
                lab1:
                    z->c = z->l - m2;
                    if (!(eq_s_b(z, 1, s_22))) { z->lb = mlimit; return 0; }
                }
            lab0:
                {   int ret = slice_del(z);
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z);
                    if (ret < 0) return ret;
                }
                break;
        }
        z->lb = mlimit;
    }
    return 1;
}
