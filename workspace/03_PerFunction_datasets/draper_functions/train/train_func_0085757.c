get_random_string_length_in_range(int minlen, int maxlen)
{
    gchar *ret;
    int i, len = get_random_int_in_range(minlen, maxlen);

    ret = g_new0(gchar, len);

    for (i = 0; i < len - 1; i++)
        ret[i] = get_random_character ();

    return g_strstrip(ret);
}
