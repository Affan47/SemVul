qof_string_number_compare_func (gpointer a, gpointer b, gint options,
                                QofParam *getter)
{
    const char *s1, *s2;
    char *sr1, *sr2;
    long i1, i2;
    g_return_val_if_fail (a && b && getter && getter->param_getfcn, COMPARE_ERROR);

    s1 = ((query_string_getter)getter->param_getfcn) (a, getter);
    s2 = ((query_string_getter)getter->param_getfcn) (b, getter);


    if (s1 == s2)  return 0;
    if (!s1 && s2) return -1;
    if (s1 && !s2) return 1;


    i1 = strtol(s1, &sr1, 10);
    i2 = strtol(s2, &sr2, 10);
    if (i1 < i2)  return -1;
    if (i1 > i2)  return 1;


    if (options == QOF_STRING_MATCH_CASEINSENSITIVE)
        return safe_strcasecmp (sr1, sr2);

    return g_strcmp0 (sr1, sr2);
}
