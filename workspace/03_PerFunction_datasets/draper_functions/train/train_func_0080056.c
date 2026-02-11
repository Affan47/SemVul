xaccSplitEqualCheckBal (const char *tag, gnc_numeric a, gnc_numeric b)
{
    char *str_a, *str_b;

    if (gnc_numeric_equal (a, b))
        return TRUE;

    str_a = gnc_numeric_to_string (a);
    str_b = gnc_numeric_to_string (b);

    PINFO ("%sbalances differ: %s vs %s", tag, str_a, str_b);

    g_free (str_a);
    g_free (str_b);

    return FALSE;
}
