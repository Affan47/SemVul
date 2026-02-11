r_mark_regions(struct SN_env * z) {
    z->I[0] = z->l;
    z->I[1] = z->l;
    {   int c = z->c;
        {   int c = z->c;
            if (!(find_among(z, a_0, 2))) goto lab2;
            goto lab1;
        lab2:
            z->c = c;
            while(1) {
                if (!(in_grouping(z, g_v, 97, 121))) goto lab3;
                break;
            lab3:
                if (z->c >= z->l) goto lab0;
                z->c++;
            }
            while(1) {
                if (!(out_grouping(z, g_v, 97, 121))) goto lab4;
                break;
            lab4:
                if (z->c >= z->l) goto lab0;
                z->c++;
            }
        }
    lab1:
        z->I[0] = z->c;
        while(1) {
            if (!(in_grouping(z, g_v, 97, 121))) goto lab5;
            break;
        lab5:
            if (z->c >= z->l) goto lab0;
            z->c++;
        }
        while(1) {
            if (!(out_grouping(z, g_v, 97, 121))) goto lab6;
            break;
        lab6:
            if (z->c >= z->l) goto lab0;
            z->c++;
        }
        z->I[1] = z->c;
    lab0:
        z->c = c;
    }
    return 1;
}
