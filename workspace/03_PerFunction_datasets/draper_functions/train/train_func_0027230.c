r_postlude(struct SN_env * z) {
    int among_var;
    while(1) {
        int c1 = z->c;
        z->bra = z->c;
        if (z->c + 1 >= z->l || z->p[z->c + 1] != 126) among_var = 3; else
        among_var = find_among(z, a_1, 3);
        if (!(among_var)) goto lab0;
        z->ket = z->c;
        switch(among_var) {
            case 0: goto lab0;
            case 1:
                {   int ret = slice_from_s(z, 2, s_2);
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 2, s_3);
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret;
                }
                break;
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}
