r_long(RFILE *p)
{
    register long x;
    register FILE *fp = p->fp;
    if (fp) {
        x = getc(fp);
        x |= (long)getc(fp) << 8;
        x |= (long)getc(fp) << 16;
        x |= (long)getc(fp) << 24;
    }
    else {
        x = rs_byte(p);
        x |= (long)rs_byte(p) << 8;
        x |= (long)rs_byte(p) << 16;
        x |= (long)rs_byte(p) << 24;
    }
#if SIZEOF_LONG > 4

    x |= -(x & 0x80000000L);
#endif
    return x;
}
