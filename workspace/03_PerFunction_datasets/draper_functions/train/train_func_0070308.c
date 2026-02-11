series_table_get_value (series_table *st, const char *s)
{
    int k = series_table_get_index(st, s);

    return (k > 0)? (double) k : NADBL;
}
