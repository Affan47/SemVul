gwy_ascii_strcase_equal(gconstpointer v1,
                        gconstpointer v2)
{
    const gchar *s1 = (const gchar*)v1, *s2 = (const gchar*)v2;

    while (*s1 && *s2) {
        if (TOLOWER(*s1) != TOLOWER(*s2))
            return FALSE;
        s1++, s2++;
    }
    return !*s1 && !*s2;
}
