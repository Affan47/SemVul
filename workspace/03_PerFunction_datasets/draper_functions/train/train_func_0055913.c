rhkspm32_read_range(const gchar *buffer,
                    const gchar *name,
                    RHKRange *range)
{
    gchar *end;
    guint pos;

    if (!g_str_has_prefix(buffer, name))
        return FALSE;
    pos = strlen(name) + 1;


    range->scale = g_ascii_strtod(buffer + pos, &end);
    if (end == buffer + pos || pos > 0x20)
        return FALSE;
    pos = end - buffer;

    range->offset = g_ascii_strtod(buffer + pos, &end);
    if (end == buffer + pos || pos > 0x20)
        return FALSE;
    pos = end - buffer;

    range->units = g_strstrip(g_strndup(buffer + pos, 0x20 - pos));
    gwy_debug("<%s> %g %g <%s>",
              name, range->scale, range->offset, range->units);

    return TRUE;
}
