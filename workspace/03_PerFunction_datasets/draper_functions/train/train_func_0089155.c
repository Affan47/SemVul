build_argv_from_strings(const gchar *first_arg, ...) {
    gchar **argv;
    va_list args;
    const gchar *str;
    GPtrArray *ptra = g_ptr_array_sized_new(20);

    if (first_arg) {
        gchar **strings = g_strsplit(first_arg, " ", 0);
        gchar **strp = strings;
        while (*strp) {
            if (**strp) {
                g_ptr_array_add(ptra, g_strdup(*strp));
            }
            ++strp;
        }
        g_strfreev(strings);
    }

    va_start (args, first_arg);
    do {
        str = va_arg (args, const gchar *);
        g_ptr_array_add(ptra, g_strdup(str));
    }
    while (str);

    va_end (args);

    argv = (gchar **) g_ptr_array_free(ptra, FALSE);

    return argv;
}
