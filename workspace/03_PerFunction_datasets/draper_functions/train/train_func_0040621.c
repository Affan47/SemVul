r_Step_5a(struct SN_env * z) {
    z->ket = z->c;
    if (!(eq_s_b(z, 1, s_26))) return 0;
    z->bra = z->c;
    {   int m1 = z->l - z->c; (void)m1;
        {   int ret = r_R2(z);
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int ret = r_R1(z);
            if (ret == 0) return 0;
            if (ret < 0) return ret;
        }
        {   int m2 = z->l - z->c; (void)m2;
            {   int ret = r_shortv(z);
                if (ret == 0) goto lab2;
                if (ret < 0) return ret;
            }
            return 0;
        lab2:
            z->c = z->l - m2;
        }
    }
lab0:
    {   int ret = slice_del(z);
        if (ret < 0) return ret;
    }
    return 1;
}
