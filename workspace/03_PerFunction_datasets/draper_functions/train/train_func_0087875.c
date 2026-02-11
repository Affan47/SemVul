mnemonic_escape (const gchar *source)
{
    const guchar *p;
    gchar *dest;
    gchar *q;

    g_return_val_if_fail (source != NULL, NULL);

    p = (guchar *) source;
    q = dest = g_malloc (strlen (source) * 2 + 1);

    while (*p)
    {
        switch (*p)
        {
        case '_':
            *q++ = '_';
            *q++ = '_';
            break;
        default:
            *q++ = *p;
            break;
        }
        p++;
    }
    *q = 0;
    return dest;
}
