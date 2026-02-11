gwy_strkill(gchar *s,
            const gchar *killchars)
{
    gchar *p, *q;
    gchar killc;

    if (!killchars || !*killchars)
        return s;
    killc = *killchars;
    if (killchars[1])
        g_strdelimit(s, killchars+1, killc);
    if ((p = strchr(s, killc))) {
        for (q = p; *p; p++) {
            if (*p != killc) {
                *q = *p;
                q++;
            }
        }
        *q = '\0';
    }

    return s;
}
