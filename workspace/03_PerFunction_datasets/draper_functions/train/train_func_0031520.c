netsnmp_fsys_calculate32( netsnmp_fsys_info *f)
{
    unsigned long long s = f->size;
    unsigned long long u = f->units;
    int factor = 0;
    while (s > INT32_MAX) {
        s = s >> 1;
        u = u << 1;
        factor++;
    }

    f->size_32 = s;
    f->units_32 = u;
    f->avail_32 = f->avail << factor;
    f->used_32 = f->used << factor;
}
