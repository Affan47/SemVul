GC_build_fl2(h, ofl)
struct hblk *h;
ptr_t ofl;
{
    register word * p = h -> hb_body;
    register word * lim = (word *)(h + 1);

    p[0] = (word)ofl;
    p[2] = (word)p;
    p += 4;
    for (; p < lim; p += 4) {
        p[0] = (word)(p-2);
        p[2] = (word)p;
    };
    return((ptr_t)(p-2));
}
