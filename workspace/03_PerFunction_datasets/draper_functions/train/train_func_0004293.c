write_longint(struct file_list *f, int64 x)
{
    char b[8];

    if (x <= 0x7FFFFFFF) {
        write_int(f, (int)x);
        return;
    }

#ifdef INT64_IS_OFF_T
    if (sizeof (int64) < 8) {
        fprintf(stderr, "write_longint: Integer overflow: attempted 64-bit offset\n");
    }
#endif

    write_int(f, (int32)0xFFFFFFFF);
    SIVAL(b,0,(x&0xFFFFFFFF));
    SIVAL(b,4,((x>>32)&0xFFFFFFFF));

    writefd(f,b,8);
}
