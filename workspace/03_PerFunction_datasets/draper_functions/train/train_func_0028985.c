hawki_tools_get_kth_float(float * a,
                                int        n,
                                int        k)
{
    register float x;
    register int    i, j, l, m;

    cpl_ensure(a, CPL_ERROR_NULL_INPUT, 0.00);

    l=0; m=n-1;
    while (l<m) {
        x=a[k];
        i=l;
        j=m;
        do {
            while (a[i]<x) i++;
            while (x<a[j]) j--;
            if (i<=j) {
                SWAP(a[i],a[j]);
                i++; j--;
            }
        } while (i<=j);
        if (j<k) l=i;
        if (k<i) m=j;
    }
    return a[k];
}
