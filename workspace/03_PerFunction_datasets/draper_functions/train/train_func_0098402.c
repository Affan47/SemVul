read_qt_bool(const guchar **p, gsize *size, gboolean *value)
{
    *value = FALSE;
    if (*size < sizeof(guchar))
        return FALSE;

    *value = !!**p;
    gwy_debug("QBool data: %d", *value);
    *size -= sizeof(guchar);
    (*p)++;

    return TRUE;
}
