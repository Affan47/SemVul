r_step_0(struct SN_env * z) {
    int among_var;
    z->ket = z->c;
    if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((266786 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0;
    among_var = find_among_b(z, a_1, 16);
    if (!(among_var)) return 0;
    z->bra = z->c;
    {   int ret = r_R1(z);
        if (ret == 0) return 0;
        if (ret < 0) return ret;
    }
    switch(among_var) {
        case 0: return 0;
        case 1:
            {   int ret = slice_del(z);
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_6);
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_7);
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 1, s_8);
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int m1 = z->l - z->c; (void)m1;
                if (!(eq_s_b(z, 2, s_9))) goto lab0;
                return 0;
            lab0:
                z->c = z->l - m1;
            }
            {   int ret = slice_from_s(z, 1, s_10);
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 2, s_11);
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 3, s_12);
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}
