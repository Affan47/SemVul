parse_uint_vector(const gchar *value,
                  guint n,
                  ...)
{
    va_list ap;
    gchar *end;
    guint i;

    va_start(ap, n);

    for (i = 0; i < n; i++) {
        guint *u = va_arg(ap, guint*);

        *u = g_ascii_strtoull(value, &end, 10);
        if (end == value) {
            va_end(ap);
            return FALSE;
        }
        value = end;
    }
    va_end(ap);

    return TRUE;
}
