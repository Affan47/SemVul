r_reflexive(struct SN_env * z) {
    int among_var;
    z->ket = z->c;
    if (z->c - 3 <= z->lb || (z->p[z->c - 1] != 140 && z->p[z->c - 1] != 143)) return 0;
    among_var = find_among_b(z, a_3, 2);
    if (!(among_var)) return 0;
    z->bra = z->c;
    switch(among_var) {
        case 0: return 0;
        case 1:
            {   int ret = slice_del(z);
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}
