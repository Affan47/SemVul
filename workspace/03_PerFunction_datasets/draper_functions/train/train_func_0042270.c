fs_decimal_init_from_int32(fs_decimal *d, int32_t i)
{
    fs_decimal_init(d);
    unsigned long long val = llabs(i);
    if (i < 0) {
        d->flags |= FS_D_NEGATIVE;
    }

    return from_uint64(d, val, 0);
}
