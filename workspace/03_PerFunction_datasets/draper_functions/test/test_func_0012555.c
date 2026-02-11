gretl_string_table_written (void)
{
    int ret = 0;

    if (paths.status & STRING_TABLE_WRITTEN) ret = 1;

    paths.status &= ~STRING_TABLE_WRITTEN;

    return ret;
}
