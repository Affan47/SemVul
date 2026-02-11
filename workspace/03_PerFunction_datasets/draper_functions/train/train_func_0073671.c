sinfo_copy_mx(Matrix a)
{
    Matrix b = sinfo_create_mx(a->nr,a->nc);
    if (b!=NULL) {
        register int s = a->nr*a->nc;
        register double *mm = b->m+s;
        register double *am = a->m+s;
        while (s--) *--mm = *--am;
    }
    return b;
}
