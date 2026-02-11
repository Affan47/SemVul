r_post_process_last_consonants(struct SN_env * z) {
    int among_var;
    z->ket = z->c;
    among_var = find_among_b(z, a_23, 4);
    if (!(among_var)) return 0;
    z->bra = z->c;
    switch(among_var) {
        case 0: return 0;
        case 1:
            {   int ret = slice_from_s(z, 1, s_16);
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 2, s_17);
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_18);
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 1, s_19);
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}
