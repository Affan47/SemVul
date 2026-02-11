init_banerjee_info()
{
    int i,j;

    m = 1;
    for(i=0; i < max_nest; i++) {
        idx_entry[i] = 0;
        idx_flg[i] = FALSE;
        uu[i] = 0;
        ll[i] = 0;
        f[i] = 0;
        a[i] = 0;
        b[i] = 0;
        for (j=0; j < max_nest; j++) {
            *(u + (i * max_nest + j)) = 0;
            *(l + (i * max_nest + j)) = 0;
        }
    }

    return;
}
