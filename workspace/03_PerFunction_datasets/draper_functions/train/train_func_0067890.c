gwy_radio_buttons_createl(GCallback callback,
                          gpointer cbdata,
                          gint current,
                          ...)
{
    GSList *group;
    GwyEnum *entries;
    gint i, nentries;
    va_list ap;

    va_start(ap, current);
    nentries = 0;
    while (va_arg(ap, const gchar*)) {
        (void)va_arg(ap, gint);
        nentries++;
    }
    va_end(ap);

    entries = g_new(GwyEnum, nentries);

    va_start(ap, current);
    for (i = 0; i < nentries; i++) {
        entries[i].name = va_arg(ap, const gchar*);
        entries[i].value = va_arg(ap, gint);
    }
    va_end(ap);

    group = gwy_radio_buttons_create_real(entries, nentries,
                                          callback, cbdata, current, FALSE);
    g_free(entries);

    return group;
}
