get_system_time(Uint32 *out)
{
    struct timeval tp;
    Uint32 sec_factor = 1000 * 1000 * 10;
    Uint32 add;
    Uint32 ah, al, bh, bl;

    gettimeofday(&tp, NULL);


    out[1] = 0x01B21DD2;
    out[0] = 0x13814000;

    add = tp.tv_usec * 10;
    if (OFStandard::check32BitAddOverflow(out[0], add))
        out[1]++;
    out[0] += add;


    ah = tp.tv_sec >> 16;
    al = tp.tv_sec & 0xffff;
    bh = sec_factor >> 16;
    bl = sec_factor & 0xffff;


    add = al*bl;
    if (OFStandard::check32BitAddOverflow(out[0], add))
        out[1]++;
    out[0] += add;

    out[1] += ah * bh;


    add = (((ah * bl) + (al * bh)) & 0xffff) << 16;
    if (OFStandard::check32BitAddOverflow(out[0], add))
        out[1]++;
    out[0] += add;

    add = (((ah * bl) + (al * bh)) & 0xffff0000) >> 16;
    out[1] += add;
}
