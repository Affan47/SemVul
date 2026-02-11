write_nulls(struct archive_write *a, size_t padding)
{
    int ret;
    size_t to_write;

    while (padding > 0) {
        to_write = padding < a->null_length ? padding : a->null_length;
        ret = (a->compressor.write)(a, a->nulls, to_write);
        if (ret != ARCHIVE_OK)
            return (ret);
        padding -= to_write;
    }
    return (ARCHIVE_OK);
}
