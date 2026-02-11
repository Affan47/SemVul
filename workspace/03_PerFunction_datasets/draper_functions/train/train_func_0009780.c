r_mark_regions(struct SN_env * z) {
    z->I[0] = z->l;
    z->I[1] = z->l;
    {   int c1 = z->c;
        {   int c2 = z->c;
            if (z->c + 4 >= z->l || z->p[z->c + 4] >> 5 != 3 || !((2375680 >> (z->p[z->c + 4] & 0x1f)) & 1)) goto lab2;
            if (!(find_among(z, a_0, 3))) goto lab2;
            goto lab1;
        lab2:
            z->c = c2;
            {
                int ret = out_grouping(z, g_v, 97, 121, 1);
                if (ret < 0) goto lab0;
                z->c += ret;
            }
            {
                int ret = in_grouping(z, g_v, 97, 121, 1);
                if (ret < 0) goto lab0;
                z->c += ret;
            }
        }
    lab1:
        z->I[0] = z->c;
        {
            int ret = out_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        {
            int ret = in_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[1] = z->c;
    lab0:
        z->c = c1;
    }
    return 1;
}
