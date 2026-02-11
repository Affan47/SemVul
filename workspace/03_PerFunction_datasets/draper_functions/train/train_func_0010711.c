r_particle_etc(struct SN_env * z) {
    int among_var;
    {   int mlimit;
        int m1 = z->l - z->c; (void)m1;
        if (z->c < z->I[0]) return 0;
        z->c = z->I[0];
        mlimit = z->lb; z->lb = z->c;
        z->c = z->l - m1;
        z->ket = z->c;
        among_var = find_among_b(z, a_0, 10);
        if (!(among_var)) { z->lb = mlimit; return 0; }
        z->bra = z->c;
        z->lb = mlimit;
    }
    switch(among_var) {
        case 0: return 0;
        case 1:
            if (in_grouping_b_U(z, g_particle_end, 97, 246, 0)) return 0;
            break;
        case 2:
            {   int ret = r_R2(z);
                if (ret == 0) return 0;
                if (ret < 0) return ret;
            }
            break;
    }
    {   int ret = slice_del(z);
        if (ret < 0) return ret;
    }
    return 1;
}
