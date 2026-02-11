r_other_suffix(struct SN_env * z) {
    int among_var;
    {   int m3;
        int m = z->l - z->c; (void) m;
        if (z->c < z->I[0]) return 0;
        z->c = z->I[0];
        m3 = z->lb; z->lb = z->c;
        z->c = z->l - m;
        z->ket = z->c;
        among_var = find_among_b(z, a_2, 5);
        if (!(among_var)) { z->lb = m3; return 0; }
        z->bra = z->c;
        switch(among_var) {
            case 0: { z->lb = m3; return 0; }
            case 1:
                {   int ret;
                    ret = slice_del(z);
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret;
                    ret = slice_from_s(z, 3, s_0);
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret;
                    ret = slice_from_s(z, 4, s_1);
                    if (ret < 0) return ret;
                }
                break;
        }
        z->lb = m3;
    }
    return 1;
}
